#include "transform.h"

#include "math/math.h"

#include <cmath>
#include <stdexcept>

namespace engine {

  Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale) : 
    m_Position{position}, m_Rotation{rotation}, m_Scale{scale}
  {
    UpdateMatrices();
  }

  void Transform::SetPosition(const Vector3& position) {
    m_Position = position;
    UpdateMatrices();
  }

  void Transform::SetRotation(const Vector3& rotation) {
    m_Rotation = rotation;
    UpdateMatrices();
  }

  void Transform::SetScale(const Vector3& scale) {
    if (scale.x < 0.0f || scale.y < 0.0f || scale.z < 0.0f) {
      throw std::invalid_argument("EXCEPTION: scale values cannot be negative");
    }

    m_Scale = scale;
    UpdateMatrices();
  }

  const Vector3& Transform::GetPosition() const { return m_Position; }

  const Vector3& Transform::GetRotation() const { return m_Rotation; }

  const Vector3& Transform::GetScale() const { return m_Scale; }

  // The default right direction is x+
  const Vector3 Transform::GetRightDirection() const {
    Vector3 right {
      m_RotationMat.matrix[0][0],
      m_RotationMat.matrix[1][0],
      m_RotationMat.matrix[2][0]
    };

    return right.GetNormalized();
  }

  // The default up direction is y-
  const Vector3 Transform::GetUpDirection() const {
    Vector3 up {
      m_RotationMat.matrix[0][1],
      m_RotationMat.matrix[1][1],
      m_RotationMat.matrix[2][1]
    };

    return up.GetNormalized();
  }

  // The default forward direction is z+
  const Vector3 Transform::GetForwardDirection() const { 
    Vector3 forward {
      m_RotationMat.matrix[0][2], 
      m_RotationMat.matrix[1][2],
      m_RotationMat.matrix[2][2]
    };

    return forward.GetNormalized(); 
  }

  const Matrix4x4& Transform::GetRotationMatrix() const { return m_RotationMat; }

  const Matrix4x4& Transform::GetModelMatrix() const { return m_ModelMat; }

  void Transform::ApplyMovement(const Vector3& movement) {
    m_Position += movement;
    UpdateMatrices();
  }

  void Transform::ApplyRotation(const Vector3& rotation) {
    m_Rotation += rotation;
    UpdateMatrices();
  }

  void Transform::UpdateMatrices() {
    Matrix4x4 translationMat{};
    translationMat.matrix[0][0] = 1.0f;
    translationMat.matrix[0][3] = m_Position.x;
    translationMat.matrix[1][1] = 1.0f;
    translationMat.matrix[1][3] = m_Position.y;
    translationMat.matrix[2][2] = 1.0f;
    translationMat.matrix[2][3] = m_Position.z;
    translationMat.matrix[3][3] = 1.0f;

    float xRotation = Math::DegreeToRadians(m_Rotation.x * 0.5f);
    float yRotation = Math::DegreeToRadians(m_Rotation.y * 0.5f);
    float zRotation = Math::DegreeToRadians(m_Rotation.z * 0.5f);

    float cosx{cosf(xRotation)}, sinx{sinf(xRotation)};
    float cosy{cosf(yRotation)}, siny{sinf(yRotation)};
    float cosz{cosf(zRotation)}, sinz{sinf(zRotation)};

    // Quaternion used for rotation
    float x = cosz * cosy * sinx;
    float y = cosz * siny * cosx + sinz * cosy * sinx;
    float z = -cosz * siny * sinx + sinz * cosy * cosx;
    float w = cosz * cosy * cosx;

    m_RotationMat.matrix[0][0] = 1.0f - 2.0f * (y * y + z * z);
    m_RotationMat.matrix[0][1] = 2.0f * (x * y - z * w);
    m_RotationMat.matrix[0][2] = 2.0f * (x * z + y * w);
    m_RotationMat.matrix[1][0] = 2.0f * (x * y + z * w);
    m_RotationMat.matrix[1][1] = 1.0f - 2.0f * (x * x + z * z);
    m_RotationMat.matrix[1][2] = 2.0f * (y * z - x * w);
    m_RotationMat.matrix[2][0] = 2.0f * (x * z - y * w);
    m_RotationMat.matrix[2][1] = 2.0f * (y * z + x * w);
    m_RotationMat.matrix[2][2] = 1.0f - 2.0f * (x * x + y * y);
    m_RotationMat.matrix[3][3] = 1.0f;
        
    Matrix4x4 scalingMat{};
    scalingMat.matrix[0][0] = m_Scale.x;
    scalingMat.matrix[1][1] = m_Scale.y;
    scalingMat.matrix[2][2] = m_Scale.z;
    scalingMat.matrix[3][3] = 1.0f;

    m_ModelMat = translationMat * m_RotationMat * scalingMat;
  }

}