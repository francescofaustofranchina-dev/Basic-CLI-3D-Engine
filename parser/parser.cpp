#include "parser.h"

#include "geometry/primitive.h"

#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

// TO-DO: improve the checks made in the f section

// The main logic is to save each vertex without duplicates. A vertex is identified
// by its position and its normal. That's the reason why the unordered_map is used

namespace engine {
  // REMEMBER: the following structs are used exclusively inside this file

  // Defines a key for an unordered_map
  struct VertexKey {
    std::size_t vIndex, vnIndex;

    bool operator==(const VertexKey& vKey) const {
      return vIndex == vKey.vIndex && vnIndex == vKey.vnIndex;
    }
  };

  // Defines a hash functior for the previous struct
  struct VertexKeyHash {
    std::size_t operator()(const VertexKey& vKey) const {
      return std::hash<std::size_t>()(vKey.vIndex)^(std::hash<std::size_t>()(vKey.vnIndex) << 1);
    }
  };

  // Retrieve a mesh from the input path
  Mesh Parser::LoadMeshFromFile(const std::string& filePath) {
    std::ifstream fStream(filePath);
    if (!fStream.is_open()) {
      throw std::invalid_argument("EXCEPTION: unable to open mesh file");
    }

    std::string line;

    std::vector<Vector3> v;                         // Vertices
    std::vector<Vector3> vn;                        // Vertex normals

    std::vector<Vertex> vertexBuffer;               // Vertices
    std::vector<std::array<std::size_t, 3>> indexBuffer; // Triangle indices

    std::unordered_map<VertexKey, std::size_t, VertexKeyHash> uniqueVertexIndices;

    while (std::getline(fStream, line)) {
      std::istringstream sStream{line};
      std::string prefix;
      sStream >> prefix;

      if (prefix == "v") {
        float x, y, z;
        if (!(sStream >> x >> y >> z)) {
          throw std::invalid_argument("EXCEPTION: invalid vertex line format");
        }

        v.emplace_back(Vector3{x, y, z});
      }
      else if (prefix == "vn") {
        float x, y, z;
        if (!(sStream >> x >> y >> z)) {
          throw std::invalid_argument("EXCEPTION: invalid normal line format");
        }

        vn.emplace_back(Vector3{x, y, z});
      }
      else if (prefix == "f") {
        constexpr std::size_t kSize{3};
        std::array<std::size_t, kSize> triIndices;

        for (std::size_t i{0}; i < kSize; ++i) {
          std::string token;
          sStream >> token;

          std::size_t slashIndex{token.find("//")};

          std::size_t vIndex{std::stoul(token.substr(0, slashIndex)) - 1};
          std::size_t vnIndex{std::stoul(token.substr(slashIndex + 2)) - 1};
          VertexKey vKey{vIndex, vnIndex};

          auto it = uniqueVertexIndices.find(vKey);
          if (it != uniqueVertexIndices.end()) {
            triIndices[i] = it->second;
          }
          else {
            vertexBuffer.emplace_back(Vertex{v[vIndex], vn[vnIndex]});

            std::size_t newIndex{static_cast<std::size_t>(vertexBuffer.size() - 1)};
            uniqueVertexIndices[vKey] = newIndex;
            triIndices[i] = newIndex;
          }
        }

        indexBuffer.push_back(triIndices);
      }
    }

    fStream.close();

    if (vertexBuffer.size() == 0 || indexBuffer.size() == 0) {
      throw std::invalid_argument("EXCEPTION: the mesh file format is not supported");
    }

    return Mesh{vertexBuffer, indexBuffer};
  }
  
}
