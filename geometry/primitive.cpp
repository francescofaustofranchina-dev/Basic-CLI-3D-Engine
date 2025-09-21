#include "primitive.h"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace engine {

  Vector2::Vector2() : x{0.0f}, y{0.0f} {}

  Vector2::Vector2(float x, float y) : x{x}, y{y} {}

  float Vector2::GetModule() const { 
    return sqrt(x * x + y * y); 
  }

  Vector2 Vector2::GetNormalized() const {
    float module{GetModule()};

    if (module == 0.0f) {
      return *this;
    }

    return Vector2{x / module, y / module};
  }

  Vector2 Vector2::operator+(const Vector2& vec) const {
    return Vector2{x + vec.x, y + vec.y};
  }

  Vector2 Vector2::operator-(const Vector2& vec) const {
    return Vector2{x - vec.x, y - vec.y};
  }

  Vector2 Vector2::operator*(float val) const {
    return Vector2{x * val, y * val};
  }

  Vector2 Vector2::operator/(float val) const {
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};

    if (std::abs(val) < epsilon) {
      throw std::invalid_argument("EXCEPTION: cannot divide by zero");
    }

    return Vector2{x / val, y / val};
  }

  Vector2& Vector2::operator+=(const Vector2& vec) {
    x += vec.x;
    y += vec.y;

    return *this;
  }

  Vector2& Vector2::operator-=(const Vector2& vec) {
    x -= vec.x;
    y -= vec.y;

    return *this;
  }

  Vector2& Vector2::operator*=(float val) {
    x *= val;
    y *= val;

    return *this;
  }

  Vector2& Vector2::operator/=(float val) {
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};

    if (std::abs(val) < epsilon) {
      throw std::invalid_argument("EXCEPTION: cannot divide by zero");
    }

    x /= val;
    y /= val;

    return *this;
  }

  Vector2 Vector2::operator-() const { return Vector2{-x, -y}; }

  bool Vector2::operator==(const Vector2& vec) const {
    constexpr float epsilon{std::numeric_limits<float>::epsilon() * 100.0f};

    return std::abs(x - vec.x) < epsilon && std::abs(y - vec.y) < epsilon;
  }
  
  Vector3::Vector3() : x{0.0f}, y{0.0f}, z{0.0f} {}
  
  Vector3::Vector3(float x, float y, float z) : x{x}, y{y}, z{z} {}

  float Vector3::GetModule() const {
    return sqrt(x * x + y * y + z * z);
  }

  Vector3 Vector3::GetNormalized() const {
    float module{GetModule()};

    if (module == 0.0f) {
      return *this;
    }

    return Vector3{x / module, y / module, z / module};
  }

  Vector3 Vector3::operator+(const Vector3& vec) const {
    return Vector3{x + vec.x, y + vec.y, z + vec.z};
  }

  Vector3 Vector3::operator-(const Vector3& vec) const {
    return Vector3{x - vec.x, y - vec.y, z - vec.z};
  }

  Vector3 Vector3::operator*(const Matrix4x4& mat) const {
    Vector3 result{};

    result.x = x * mat.matrix[0][0] + y * mat.matrix[1][0] +
      z * mat.matrix[2][0] + mat.matrix[3][0];
    result.y = x * mat.matrix[0][1] + y * mat.matrix[1][1] +
      z * mat.matrix[2][1] + mat.matrix[3][1];
    result.z = x * mat.matrix[0][2] + y * mat.matrix[1][2] +
      z * mat.matrix[2][2] + mat.matrix[3][2];

    // A fourth unitary component is considered for the input Vector3, so
    // even the result has a fourth component, called w
    float w = x * mat.matrix[0][3] + y * mat.matrix[1][3] +
      z * mat.matrix[2][3] + mat.matrix[3][3];

    constexpr float epsilon{std::numeric_limits<float>::epsilon()};

    if (std::abs(w) < epsilon) {
      throw std::invalid_argument("EXCEPTION: cannot divide by zero");
    }

    result /= w;

    return result;
  }

  Vector3 Vector3::operator*(float val) const {
    return Vector3{x * val, y * val, z * val};
  }

  Vector3 Vector3::operator/(float val) const {
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};

    if (std::abs(val) < epsilon) {
      throw std::invalid_argument("EXCEPTION: cannot divide by zero");
    }

    return Vector3{x / val, y / val, z / val};
  }

  Vector3& Vector3::operator+=(const Vector3& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
  }

  Vector3& Vector3::operator-=(const Vector3& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
  }

  Vector3& Vector3::operator*=(float val) {
    x *= val;
    y *= val;
    z *= val;

    return *this;
  }

  Vector3& Vector3::operator/=(float val) {
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};

    if (std::abs(val) < epsilon) {
      throw std::invalid_argument("EXCEPTION: cannot divide by zero");
    }

    x /= val;
    y /= val;
    z /= val;

    return *this;
  }

  Vector3 Vector3::operator-() const { return Vector3{-x, -y, -z}; }

  bool Vector3::operator==(const Vector3& vec) const {
    constexpr float epsilon{std::numeric_limits<float>::epsilon() * 100.0f};

    return std::abs(x - vec.x) < epsilon && std::abs(y - vec.y) < epsilon &&
      std::abs(z - vec.z) < epsilon;
  }

  Matrix4x4::Matrix4x4() : matrix{} {}

  Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const {
    Matrix4x4 result{};

    for (std::size_t i{0}; i < result.matrix.size(); ++i) {
      for (std::size_t j{0}; j < result.matrix[0].size(); ++j) {
        result.matrix[i][j] = matrix[i][j] + mat.matrix[i][j];
      }
    }

    return std::move(result);
  }

  Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mat) const {
    Matrix4x4 result{};

    for (std::size_t i{0}; i < result.matrix.size(); ++i) {
      for (std::size_t j{0}; j < result.matrix[0].size(); ++j) {
        result.matrix[i][j] = matrix[i][j] - mat.matrix[i][j];
      }
    }

    return std::move(result);
  }

  Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const {
    Matrix4x4 result{};
        
    for (std::size_t i{0}; i < result.matrix.size(); ++i) {
      for (std::size_t j{0}; j < result.matrix[0].size(); ++j) {
        for (std::size_t k{0}; k < result.matrix.size(); ++k) {
          result.matrix[i][j] += matrix[i][k] * mat.matrix[k][j];
        }
      }
    }

    return std::move(result);
  }

  Vector3 Matrix4x4::operator*(const Vector3& vec) const {
    Vector3 result{};

    result.x = matrix[0][0] * vec.x + matrix[0][1] * vec.y +
      matrix[0][2] * vec.z + matrix[0][3];
    result.y = matrix[1][0] * vec.x + matrix[1][1] * vec.y +
      matrix[1][2] * vec.z + matrix[1][3];
    result.z = matrix[2][0] * vec.x + matrix[2][1] * vec.y +
      matrix[2][2] * vec.z + matrix[2][3];

    // A fourth unitary component is considered for the input Vector3, so
    // even the result has a fourth component, called w
    float w = matrix[3][0] * vec.x + matrix[3][1] * vec.y +
      matrix[3][2] * vec.z + matrix[3][3];

    constexpr float epsilon{std::numeric_limits<float>::epsilon()};

    if (std::abs(w) < epsilon) {
      throw std::invalid_argument("EXCEPTION: cannot divide by zero");
    }

    result /= w;

    return result;
  }

  Matrix4x4 Matrix4x4::operator*(float val) const {
    Matrix4x4 result{};

    for (std::size_t i{0}; i < result.matrix.size(); ++i) {
      for (std::size_t j{0}; j < result.matrix[0].size(); ++j) {
        result.matrix[i][j] = matrix[i][j] * val;
      }
    }

    return std::move(result);
  }

  Matrix4x4 Matrix4x4::operator/(float val) const {
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};

    if (std::abs(val) < epsilon) {
      throw std::invalid_argument("EXCEPTION: cannot divide by zero");
    }

    Matrix4x4 result{};

    for (std::size_t i{0}; i < result.matrix.size(); ++i) {
      for (std::size_t j{0}; j < result.matrix[0].size(); ++j) {
        result.matrix[i][j] = matrix[i][j] / val;
      }
    }

    return std::move(result);
  }

  Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& mat) {
    for (std::size_t i{0}; i < matrix.size(); ++i) {
      for (std::size_t j{0}; j < matrix[0].size(); ++j) {
        matrix[i][j] += mat.matrix[i][j];
      }
    }

    return *this;
  }

  Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& mat) {
    for (std::size_t i{0}; i < matrix.size(); ++i) {
      for (std::size_t j{0}; j < matrix[0].size(); ++j) {
        matrix[i][j] -= mat.matrix[i][j];
      }
    }

    return *this;
  }

  Matrix4x4& Matrix4x4::operator*=(float val) {
    for (std::size_t i{0}; i < matrix.size(); ++i) {
      for (std::size_t j{0}; j < matrix[0].size(); ++j) {
        matrix[i][j] *= val;
      }
    }

    return *this;
  }

  Matrix4x4& Matrix4x4::operator/=(float val) {
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};

    if (std::abs(val) < epsilon) {
      throw std::invalid_argument("EXCEPTION: cannot divide by zero");
    }

    for (std::size_t i{0}; i < matrix.size(); ++i) {
      for (std::size_t j{0}; j < matrix[0].size(); ++j) {
        matrix[i][j] /= val;
      }
    }

    return *this;
  }

  Matrix4x4 Matrix4x4::operator-() const {
    Matrix4x4 result{};

    for (std::size_t i{0}; i < result.matrix.size(); ++i) {
      for (std::size_t j{0}; j < result.matrix[0].size(); ++j) {
        result.matrix[i][j] = -matrix[i][j];
      }
    }

    return std::move(result);
  }

  bool Matrix4x4::operator==(const Matrix4x4& mat) const {
    constexpr float epsilon{std::numeric_limits<float>::epsilon() * 100.0f};

    for (std::size_t i{0}; i < matrix.size(); ++i) {
      for (std::size_t j{0}; j < matrix[0].size(); ++j) {
        if (std::abs(matrix[i][j] - mat.matrix[i][i]) >= epsilon) {
          return false;
        }
      }
    }

    return true;
  }
  
}
