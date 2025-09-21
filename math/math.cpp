#include "math.h"

#include <cstddef>

namespace engine {
  constexpr float Math::k_Pi;

  Vector3 Math::CrossProduct(const Vector2& v1, const Vector2& v2) {
    return Vector3{0.0f, 0.0f, v1.x * v2.y - v1.y * v2.x};
  }

  Vector3 Math::CrossProduct(const Vector3& v1, const Vector3& v2){
    return Vector3 {
      v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x
    };
  }

  float Math::DotProduct(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
  }

  float Math::DotProduct(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }

  float Math::DegreeToRadians(float angle) { return angle / 180.0f * k_Pi; }
  
}
