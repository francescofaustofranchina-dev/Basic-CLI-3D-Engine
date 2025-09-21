#ifndef PARSER_H
#define PARSER_H

#include "entity/component/mesh/mesh.h"

#include <array>
#include <string>

namespace engine {
  class Parser {
  public:
    Parser() = delete;

    static Mesh LoadMeshFromFile(const std::string& filePath);
  };
  
}

#endif
