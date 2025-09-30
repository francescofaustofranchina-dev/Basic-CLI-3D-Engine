#ifndef MESH_H
#define MESH_H

#include "geometry/primitive.h"

#include <array>
#include <vector>

// Meshes are made of vertices, and a triangle contains 3 vertices.
// All the vertices are inside the vertexBuffer, and the triangles
// are reconstructed from the indexBuffer

namespace engine {

  class Mesh {
  public:
    std::vector<Vertex> vertexBuffer;                     // Vertices
    std::vector<std::array<std::size_t, 3>> indexBuffer;  // Indices of the vertices of each triangle
    std::vector<Vector3> triNormals;                      // Normals of each triangle
    std::vector<float> triBrightness;                     // Brightness of each triangle
        
    Mesh(const std::vector<Vertex>& vertexBuffer, const std::vector<std::array<std::size_t, 3>>& indexBuffer);
  };
  
}

#endif
