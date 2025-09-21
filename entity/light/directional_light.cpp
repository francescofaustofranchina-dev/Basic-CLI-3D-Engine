#include "directional_light.h"

#include <stdexcept>

namespace engine {

  DirectionalLight::DirectionalLight(float intensity, const EntityInputData& entityInputData) : Entity(entityInputData) {
    SetIntensity(intensity);
  }

  void DirectionalLight::SetIntensity(float intensity) {
    if (intensity <= 0.0f) {
      throw std::out_of_range("EXCEPTION: the intensity of a directional light must be greater than 0");
    }

    m_Intensity = intensity;
  }

  float DirectionalLight::GetIntensity() const { return m_Intensity; }
  
}
