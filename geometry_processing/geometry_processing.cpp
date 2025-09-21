#include "geometry_processing.h"

#include "math/math.h"

#include <array>
#include <vector>

// TO-DO: add clipping operations right after HandleBackfaceCulling()

namespace engine {
    
  GeometryProcessing::GeometryProcessing(const Screen& screen) : m_Screen{screen} {}

  Mesh GeometryProcessing::GetProcessedMesh(Scene& scene) {
    CalculateViewMatrix(scene.camera);

    if (scene.camera.IsProjectionDirty()) {
      CalculateProjectionMatrix(scene.camera);
    }

    Mesh processedMesh = scene.object3D.GetTransformedMesh();

    CalculateTriNormals(processedMesh);

    HandleBackfaceCulling(processedMesh, scene.camera);
    HandleFlatShading(processedMesh, scene.directionalLight);
    HandleViewSpace(processedMesh);
    HandleProjection(processedMesh);
    HandleScreenMapping(processedMesh);

    return processedMesh;
  }

  void GeometryProcessing::CalculateViewMatrix(Camera& camera) {
    Vector3 cameraRight{camera.GetTransform().GetRightDirection()};
    Vector3 cameraUp{camera.GetTransform().GetUpDirection()};
    Vector3 cameraForward{camera.GetTransform().GetForwardDirection()};

    Vector3 cameraPosition{camera.GetTransform().GetPosition()};

    m_ViewMat.matrix[0][0] = cameraRight.x;
    m_ViewMat.matrix[0][1] = cameraUp.x;
    m_ViewMat.matrix[0][2] = cameraForward.x;
    m_ViewMat.matrix[1][0] = cameraRight.y;
    m_ViewMat.matrix[1][1] = cameraUp.y;
    m_ViewMat.matrix[1][2] = cameraForward.y;
    m_ViewMat.matrix[2][0] = cameraRight.z;
    m_ViewMat.matrix[2][1] = cameraUp.z;
    m_ViewMat.matrix[2][2] = cameraForward.z;
    m_ViewMat.matrix[3][0] = -Math::DotProduct(cameraRight, cameraPosition);
    m_ViewMat.matrix[3][1] = -Math::DotProduct(cameraUp, cameraPosition);
    m_ViewMat.matrix[3][2] = -Math::DotProduct(cameraForward, cameraPosition);
    m_ViewMat.matrix[3][3] = 1.0f;
  }

  void GeometryProcessing::CalculateProjectionMatrix(Camera& camera) {
    float q{camera.GetZFar() / (camera.GetZFar() - camera.GetZNear())};

    m_ProjectionMat.matrix[0][0] = m_Screen.GetAspectRatio() * m_Screen.GetAspectRatio();
    m_ProjectionMat.matrix[1][1] = camera.GetFovRad();
    m_ProjectionMat.matrix[2][2] = q;
    m_ProjectionMat.matrix[2][3] = 1.0f;
    m_ProjectionMat.matrix[3][2] = -q * camera.GetZNear();

    camera.ClearProjectionDirty();
  }

  // Calculate the normal vector of the triangles of the mesh taking advantage 
  // of the clock-wise order of the vertices. The vertices are first translated
  // so that adjacent lines originate at (0, 0, 0), then their cross product
  // is calculated
  void GeometryProcessing::CalculateTriNormals(Mesh& processedMesh) const {
    const auto& vertexBuffer{processedMesh.vertexBuffer};
    const auto& indexBuffer{processedMesh.indexBuffer};
    auto& triNormals{processedMesh.triNormals};

    triNormals.resize(indexBuffer.size());

    for (std::size_t i{0}; i < indexBuffer.size(); ++i) {
      const auto& triIndices{indexBuffer[i]};

      std::array<Vector3, 2> edges {
        Vector3{vertexBuffer[triIndices[1]].position - vertexBuffer[triIndices[0]].position},
        Vector3{vertexBuffer[triIndices[2]].position - vertexBuffer[triIndices[0]].position}
      };

      triNormals[i] = Math::CrossProduct(edges[0], edges[1]);
    }
  }

  void GeometryProcessing::HandleBackfaceCulling(Mesh& processedMesh, const Camera& camera) const {
    const auto& vertexBuffer{processedMesh.vertexBuffer};
    const auto& indexBuffer{processedMesh.indexBuffer};
    const auto& triNormals{processedMesh.triNormals};

    std::vector<std::array<std::size_t, 3>> newIndexBuffer;
    newIndexBuffer.reserve(indexBuffer.size());

    std::vector<Vector3> newTriNormals;
    newTriNormals.reserve(triNormals.size());

    for (std::size_t i{0}; i < indexBuffer.size(); ++i) {
      const auto& triIndices{indexBuffer[i]};

      // The ray goes from the camera to a point of the current triangle
      Vector3 cameraRay{vertexBuffer[triIndices[0]].position - camera.GetTransform().GetPosition()};

      // Checks if the triangle is facing the camera. If the vectors are aligned,
      // then the triangle should be visible
      bool isTriFrontFaced{Math::DotProduct(triNormals[i], cameraRay) < 0.0f};

      if (isTriFrontFaced) {
        newIndexBuffer.push_back(indexBuffer[i]);
        newTriNormals.push_back(triNormals[i]);
      }
    }

    processedMesh.indexBuffer = std::move(newIndexBuffer);
    processedMesh.triNormals = std::move(newTriNormals);
  }

  void GeometryProcessing::HandleFlatShading(Mesh& processedMesh, const DirectionalLight& directionalLight) const {
    const auto& triNormals{processedMesh.triNormals};
    auto& triBrightness{processedMesh.triBrightness};
        
    triBrightness.resize(triNormals.size());

    constexpr float kDiffuseReflectionCoefficient{0.8f};    // Based on Lambertian reflectance model

    for (std::size_t i{0}; i < triBrightness.size(); ++i) {
      float brightness{
        Math::DotProduct(triNormals[i].GetNormalized(), directionalLight.GetTransform().GetForwardDirection())
      };
            
      triBrightness[i] = std::min(
        kDiffuseReflectionCoefficient * std::max(0.0f, brightness) * directionalLight.GetIntensity(), 1.0f
      );
    }
  }

  // Converts world space coordinates into view space coordinates
  void GeometryProcessing::HandleViewSpace(Mesh& processedMesh) const {
    auto& vertexBuffer{processedMesh.vertexBuffer};

    for (auto& v : vertexBuffer) {
      v.position = v.position * m_ViewMat;  // WARNING: it may be necessary to do the same to the normals
    }
  }

  // Projects the mesh to the screen multiplying it by the projection matrix
  void GeometryProcessing::HandleProjection(Mesh& processedMesh) const {
    auto& vertexBuffer{processedMesh.vertexBuffer};

    for (auto& v : vertexBuffer) {
      v.position = v.position * m_ProjectionMat;
    }
  }

  // This function is necessary as the engine uses a normalized
  // screen space, where both axes have values within the range [-1,1]. 
  // Therefore, the vertices of each triangle in a mesh must be scaled
  // accordingly before rendering
  void GeometryProcessing::HandleScreenMapping(Mesh& processedMesh) const {
    auto& vertexBuffer{processedMesh.vertexBuffer};

    for (auto& v : vertexBuffer) {
      v.position.x = (v.position.x + 1.0f) * 0.5f * static_cast<float>(m_Screen.GetWidth());
      v.position.y = (v.position.y + 1.0f) * 0.5f * static_cast<float>(m_Screen.GetHeight());
    }
  }
  
}
