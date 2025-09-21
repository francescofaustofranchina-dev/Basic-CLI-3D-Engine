#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include "entity/component/mesh/mesh.h"
#include "geometry/primitive.h"
#include "screen/screen.h"

#include <array>
#include <vector>

namespace engine {

  class Rasterization {
  public:
    Rasterization(Screen& screen);

    void RasterizeMesh(const Mesh& mesh);

  private:
    Screen& m_Screen;
    int m_XMin, m_XMax;
    int m_YMin, m_YMax;
    const std::array<char, 10> m_PixelChars;
    std::vector<float> m_ZBuffer;

    void SetupTriBorders(const Vertex& v1, const Vertex& v2, const Vertex& v3);
    void TraverseTri(const Vertex& v1, const Vertex& v2, const Vertex& v3, float triBrightness);
        
    void HandlePixelShading(int x, int y, float triBrightness, float zValue);
    void HandleMerging(int x, int y, char pixelChar, float zValue);

    bool IsPointInsideTri(const Vector2& point, const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
    float CalculateZValue(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vector2& point) const;
  };
  
}

#endif
