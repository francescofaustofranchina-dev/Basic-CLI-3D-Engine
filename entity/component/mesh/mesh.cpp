#include "mesh.h"

namespace engine {
  
  Mesh::Mesh(const std::vector<Vertex>& vertexBuffer, const std::vector<std::array<std::size_t, 3>>& indexBuffer) : 
    vertexBuffer{std::move(vertexBuffer)}, 
    indexBuffer{std::move(indexBuffer)} 
  {}
  
}
