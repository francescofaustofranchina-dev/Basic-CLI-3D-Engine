#ifndef ENTITY_H
#define ENTITY_H

#include "entity/component/transform/transform.h"

namespace engine {

  struct EntityInputData {
    Vector3 position{0.0f, 0.0f, 0.0f};
    Vector3 rotation{0.0f, 0.0f, 0.0f};
    Vector3 scale{1.0f, 1.0f, 1.0f};
  };

  class Entity {
  public:
    // Getters
    const Transform& GetTransform() const;
    Transform& GetTransform();

  protected:
    Entity(const EntityInputData& entityInputData);

    Transform m_Transform;
  };
  
}

#endif
