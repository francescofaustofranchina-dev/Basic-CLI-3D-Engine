#include "entity.h"

namespace engine {
  
  Entity::Entity(const EntityInputData& entityInputData) : 
    m_Transform{entityInputData.position, entityInputData.rotation, entityInputData.scale} 
  {}

  const Transform& Entity::GetTransform() const { return m_Transform; }

  Transform& Entity::GetTransform() { return m_Transform; }
  
}
