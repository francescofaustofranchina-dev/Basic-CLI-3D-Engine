#ifndef CAMERA_H
#define CAMERA_H

#include "entity/entity.h"

namespace engine {
    
  class Camera : public Entity {
  public:
    Camera(float fovDeg, float zNear, float zFar, const EntityInputData& entityInputData = EntityInputData{});

    // Setters
    void SetFovDeg(float fovDeg);
    void SetZNear(float zNear);
    void SetZFar(float zFar);

    // Getters
    float GetFovDeg() const;
    float GetFovRad() const;
    float GetZNear() const;
    float GetZFar() const;
    bool IsProjectionDirty() const;

    void ClearProjectionDirty();

  private:
    float m_FovDeg;             // Field of view
    float m_ZNear, m_ZFar;      // The nearest and the farthest rendering distance
    bool m_ProjectionDirty;     // Tells when the projection matrix should be updated
  };
  
}

#endif
