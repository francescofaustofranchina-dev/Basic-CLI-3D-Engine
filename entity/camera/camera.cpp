#include "camera.h"

#include "math/math.h"

#include <cmath>
#include <stdexcept>

namespace engine {

  Camera::Camera(float fovDeg, float zNear, float zFar, const EntityInputData& entityInputData) : Entity(entityInputData) {
    SetFovDeg(fovDeg);
    SetZNear(zNear);
    SetZFar(zFar);
  }

  void Camera::SetFovDeg(float fovDeg) {
    if (fovDeg <= 0.0f || fovDeg >= 180.0f) {
      throw std::out_of_range("EXCEPTION: FOV must be between 0 and 180 degrees");
    }

    m_FovDeg = fovDeg;
    m_ProjectionDirty = true;
  }

  void Camera::SetZNear(float zNear) {
    if (zNear <= 0.0f) {
      throw std::out_of_range("EXCEPTION: zNear must be greater than 0");
    }

    m_ZNear = zNear;
    m_ProjectionDirty = true;
  }

  void Camera::SetZFar(float zFar) {
    if (zFar <= m_ZNear) {
      throw std::out_of_range("EXCEPTION: zFar must be greater than zNear");
    }

    m_ZFar = zFar;
    m_ProjectionDirty = true;
  }

  float Camera::GetFovDeg() const { return m_FovDeg; }

  float Camera::GetFovRad() const { 
    return 1.0f / tan(Math::DegreeToRadians(m_FovDeg) * 0.5f); 
  }

  float Camera::GetZNear() const { return m_ZNear; }

  float Camera::GetZFar() const { return m_ZFar; }

  bool Camera::IsProjectionDirty() const { return m_ProjectionDirty; }

  void Camera::ClearProjectionDirty() { m_ProjectionDirty = false; }

}