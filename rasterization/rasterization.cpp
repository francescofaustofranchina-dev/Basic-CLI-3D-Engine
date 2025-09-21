#include "rasterization.h"

#include "math/math.h"

#include <algorithm>
#include <limits>

namespace engine {
    
  Rasterization::Rasterization(Screen& screen) : 
    m_Screen{screen}, 
    m_PixelChars{'.', ':', '-', '~', '=', '+', '*', '#', '%', '@'} 
  {}

  void Rasterization::RasterizeMesh(const Mesh& mesh) {
    std::size_t resolution{static_cast<std::size_t>(m_Screen.GetWidth()) * static_cast<std::size_t>(m_Screen.GetHeight())};

    if (m_ZBuffer.size() != resolution) {
      m_ZBuffer.resize(resolution);
    }

    // Set all the z-values to +infinity
    std::fill(m_ZBuffer.begin(), m_ZBuffer.end(), std::numeric_limits<float>::infinity());

    const auto& vertexBuffer{mesh.vertexBuffer};
    const auto& indexBuffer{mesh.indexBuffer};
    const auto& triBrightness{mesh.triBrightness};

    for (std::size_t i{0}; i < indexBuffer.size(); ++i) {
      const auto& triIndices{indexBuffer[i]};

      const Vertex& v1{vertexBuffer[triIndices[0]]};
      const Vertex& v2{vertexBuffer[triIndices[1]]};
      const Vertex& v3{vertexBuffer[triIndices[2]]};

      SetupTriBorders(v1, v2, v3);
      TraverseTri(v1, v2, v3, triBrightness[i]);
    }
  }

  void Rasterization::SetupTriBorders(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
    std::pair<float, float> pairFloat;
        
    pairFloat = std::minmax({v1.position.x, v2.position.x, v3.position.x});
    m_XMin = static_cast<int>(pairFloat.first);
    m_XMax = static_cast<int>(pairFloat.second);

    pairFloat = std::minmax({v1.position.y, v2.position.y, v3.position.y});
    m_YMin = static_cast<int>(pairFloat.first);
    m_YMax = static_cast<int>(pairFloat.second);
  }

  void Rasterization::TraverseTri(const Vertex& v1, const Vertex& v2, const Vertex& v3, float triBrightness) {
    for (int y{m_YMax}; y >= m_YMin; --y) {
      for (int x{m_XMin}; x <= m_XMax; ++x) {
        if (m_Screen.IsPixelValid(x, y)) {
          Vector2 point{static_cast<float>(x), static_cast<float>(y)};

          if (IsPointInsideTri(point, v1, v2, v3)) {
            float zValue{CalculateZValue(v1, v2, v3, point)};
            HandlePixelShading(x, y, triBrightness, zValue);
          }
        }
      }
    }
  }

  void Rasterization::HandlePixelShading(int x, int y, float triBrightness, float zValue) {
    std::size_t index = static_cast<std::size_t>(triBrightness * static_cast<float>((m_PixelChars.size() - 1)));
    index = std::min(index, m_PixelChars.size() - 1);

    HandleMerging(y, x, m_PixelChars[index], zValue);
  }

  void Rasterization::HandleMerging(int row, int col, char pixelChar, float zValue) {
    std::size_t index{static_cast<std::size_t>(row) * m_Screen.GetWidth() + static_cast<std::size_t>(col)};

    if (zValue < m_ZBuffer[index]) {
      m_ZBuffer[index] = zValue;
      m_Screen.SetScreenPixel(row, col, pixelChar);
    }
  }

  bool Rasterization::IsPointInsideTri(const Vector2& point, const Vertex& v1, const Vertex& v2, const Vertex& v3) const {
    // Contains the vertices of the triangle mapped on the screen
    std::array<Vector2, 3> verts {
      Vector2{v1.position.x, v1.position.y},
      Vector2{v2.position.x, v2.position.y},
      Vector2{v3.position.x, v3.position.y}
    };

    // Contains the edges of the triangle
    std::array<Vector2, 3> edges {
      Vector2{verts[1] - verts[0]},
      Vector2{verts[2] - verts[1]},
      Vector2{verts[0] - verts[2]}
    };

    // The <= operator is used because the vertices are ordered clock-wise
    return Math::CrossProduct(edges[0], point - verts[0]).z <= 0.0f &&
      Math::CrossProduct(edges[1], point - verts[1]).z <= 0.0f &&
      Math::CrossProduct(edges[2], point - verts[2]).z <= 0.0f;
  }

  // This function uses the plane's equation (ax + by + cz + d = 0) to calculate
  // the z-value of a point inside a triangle
  float Rasterization::CalculateZValue(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vector2& point) const {
    std::array<Vector3, 2> edges {
      Vector3{v2.position - v1.position},
      Vector3{v3.position - v1.position}
    };

    // The vector's components represents the coefficients of the plane's equation (x = a, y = b, z = c)
    Vector3 triNormal{Math::CrossProduct(edges[0], edges[1])};

    if (triNormal.z == 0.0f) {
      return std::numeric_limits<float>::infinity();
    }
    else {
      float d{-Math::DotProduct(triNormal, v1.position)};

      return -(triNormal.x * point.x + triNormal.y * point.y + d) / triNormal.z;
    }
  }
  
}
