#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "entity/entity.h"
#include "entity/component/mesh/mesh.h"
#include "geometry/primitive.h"

namespace engine {
  
  class Object3D : public Entity {
  public:
    Object3D(const Mesh& mesh, const EntityInputData& entityInputData = EntityInputData{});

    // Getter
    Mesh GetTransformedMesh() const;

  private:
    Mesh m_Mesh;
  };
  
}

#endif
