#ifndef GEOMETRY_PROCESSING_H
#define GEOMETRY_PROCESSING_H

#include "entity/camera/camera.h"
#include "entity/component/mesh/mesh.h"
#include "entity/light/directional_light.h"
#include "geometry/primitive.h"
#include "scene/scene.h"
#include "screen/screen.h"

namespace engine {
    
  class GeometryProcessing {
  public:
    GeometryProcessing(const Screen& screen);

    Mesh GetProcessedMesh(Scene& scene);

  private:
    const Screen& m_Screen;
    Matrix4x4 m_ViewMat;        // Used for camera view
    Matrix4x4 m_ProjectionMat;  // Used for perspective projections

    void CalculateViewMatrix(Camera& camera);
    void CalculateProjectionMatrix(Camera& camera);
    void CalculateTriNormals(Mesh& processedMesh) const;

    // Phase handlers
    void HandleBackfaceCulling(Mesh& processedMesh, const Camera& camera) const;
    void HandleFlatShading(Mesh& processedMesh, const DirectionalLight& directionalLight) const;
    void HandleViewSpace(Mesh& processedMesh) const;
    void HandleProjection(Mesh& processedMesh) const;
    void HandleScreenMapping(Mesh& processedMeshPtr) const;
  };
  
}

#endif
