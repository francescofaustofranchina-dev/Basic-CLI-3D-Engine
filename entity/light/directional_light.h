#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "entity/entity.h"

namespace engine {
    
  class DirectionalLight : public Entity {
  public:
    DirectionalLight(float intensity, const EntityInputData& entityInputData = EntityInputData{});

    // Setter
    void SetIntensity(float intensity);

    // Getter
    float GetIntensity() const;

  private:
    float m_Intensity;
  };

}

#endif
