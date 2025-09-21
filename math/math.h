#ifndef MATH_H
#define MATH_H

#include "geometry/primitive.h"

namespace engine {
    
  class Math {
  public:
    Math() = delete;
        
    // Constant
    static constexpr float k_Pi{3.14159f};

    // Operations
    static Vector3 CrossProduct(const Vector2& v1, const Vector2& v2);
    static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);
    static float DotProduct(const Vector2& v1, const Vector2& v2);
    static float DotProduct(const Vector3& v1, const Vector3& v2);

    // Conversion
    static float DegreeToRadians(float angle);
  };
  
}

#endif
