#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "geometry/primitive.h"

namespace engine {

  class Transform {
  public:
    Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale);

    // Setters
    void SetPosition(const Vector3& location);
    void SetRotation(const Vector3& rotation);
    void SetScale(const Vector3& scale);

    // Getters
    const Vector3& GetPosition() const;
    const Vector3& GetRotation() const;
    const Vector3& GetScale() const;
    const Vector3 GetRightDirection() const;
    const Vector3 GetUpDirection() const;
    const Vector3 GetForwardDirection() const;
    const Matrix4x4& GetRotationMatrix() const;
    const Matrix4x4& GetModelMatrix() const;

    // These functions must be used to apply dynamic 
    // transformations frame by frame
    void ApplyMovement(const Vector3& movement);
    void ApplyRotation(const Vector3& rotation);

  private:
    Vector3 m_Position;       // Referred to the center of an Entity (Camera, DirectionalLight, Object3D)
    Vector3 m_Rotation;       // Values are in degrees
    Vector3 m_Scale;

    Matrix4x4 m_RotationMat;  // Contains the data relating to rotation
                              // (used for the forward vector and for the
                              // vertex normals)
    Matrix4x4 m_ModelMat;     // Contains the data relating to location,
                              // rotation, and scale

    void UpdateMatrices();
  };
  
}

#endif
