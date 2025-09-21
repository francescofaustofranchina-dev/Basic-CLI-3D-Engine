#include "application/application.h"

#include <cstdlib>
#include <iostream>

namespace engine {

  int start(int argc, char** argv) {
    try {
      Application application{};
      application.Start(argc, argv);
      application.Run();

      return EXIT_SUCCESS;
    }
    catch(const std::exception& e) {
      std::cerr << e.what() << '\n';
      
      return EXIT_FAILURE;
    }
  }
  
}

int main(int argc, char** argv) {
    return engine::start(argc, argv);
}
