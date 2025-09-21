#include "object3d.h"

namespace engine {

  Object3D::Object3D(const Mesh& mesh, const EntityInputData& entityInputData) : 
    Entity(entityInputData), m_Mesh{std::move(mesh)} 
  {}

  Mesh Object3D::GetTransformedMesh() const {
    const Matrix4x4 modelMat{m_Transform.GetModelMatrix()};
    const Matrix4x4 rotationMat{m_Transform.GetRotationMatrix()};

    Mesh transformedMesh{m_Mesh};

    for (auto& v : transformedMesh.vertexBuffer) {
      v.position = modelMat * v.position;
      v.normal = (rotationMat * v.normal).GetNormalized();    
    }
      
    return std::move(transformedMesh);
  }
  
}
