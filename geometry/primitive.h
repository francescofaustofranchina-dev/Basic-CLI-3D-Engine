#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <array>

namespace engine {

  // Forward declaration
  struct Matrix4x4;

  struct Vector2 {
    Vector2();
    Vector2(float x, float y);
    
    // Coordinates (x = right, y = bottom)
    float x{0.0f}, y{0.0f};

    float GetModule() const;
    Vector2 GetNormalized() const;

    // Operators overloading
    Vector2 operator+(const Vector2& vec) const;
    Vector2 operator-(const Vector2& vec) const;
    Vector2 operator*(float val) const;
    Vector2 operator/(float val) const;
    Vector2& operator+=(const Vector2& vec);
    Vector2& operator-=(const Vector2& vec);
    Vector2& operator*=(float val);
    Vector2& operator/=(float val);
    Vector2 operator-() const;
    bool operator==(const Vector2& vec) const;
  };

  struct Vector3 {
    Vector3();
    Vector3(float x, float y, float z);
    
    // Coordinates (x = right, y = bottom, z = forward)
    float x{0.0f}, y{0.0f}, z{0.0f};

    float GetModule() const;
    Vector3 GetNormalized() const;

    // Operators overloading
    Vector3 operator+(const Vector3& vec) const;
    Vector3 operator-(const Vector3& vec) const;
    Vector3 operator*(const Matrix4x4& mat) const;
    Vector3 operator*(float val) const;
    Vector3 operator/(float val) const;
    Vector3& operator+=(const Vector3& vec);
    Vector3& operator-=(const Vector3& vec);
    Vector3& operator*=(float val);
    Vector3& operator/=(float val);
    Vector3 operator-() const;
    bool operator==(const Vector3& vec) const;
  };

  struct Vertex {
    Vector3 position;
    Vector3 normal;     // NOT USED YET
  };

  struct Matrix4x4 {
    // It contains zeros only by default
    std::array<std::array<float, 4>, 4> matrix;

    Matrix4x4();

    // Operators overloading
    Matrix4x4 operator+(const Matrix4x4& mat) const;
    Matrix4x4 operator-(const Matrix4x4& mat) const;
    Matrix4x4 operator*(const Matrix4x4& mat) const;
    Vector3 operator*(const Vector3& vec) const;
    Matrix4x4 operator*(float val) const;
    Matrix4x4 operator/(float val) const;
    Matrix4x4& operator+=(const Matrix4x4& mat);
    Matrix4x4& operator-=(const Matrix4x4& mat);
    Matrix4x4& operator*=(float val);
    Matrix4x4& operator/=(float val);
    Matrix4x4 operator-() const;
    bool operator==(const Matrix4x4& mat) const;
  };
  
}

#endif
