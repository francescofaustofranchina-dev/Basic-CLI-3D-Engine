#ifndef APPLICATION_H
#define APPLICATION_H

#include "geometry/primitive.h"
#include "geometry_processing/geometry_processing.h"
#include "rasterization/rasterization.h"
#include "scene/scene.h"
#include "screen/screen.h"

#include <memory>

// This script defines the core of the engine, that is, what
// handles the whole rendering process, from the elaboration
// of the scene to its printing on the screen

namespace engine {
    
  enum class State {
    Ready,
    Starting,
    Running,
    Shutting
  };
        
  class Application {
  public:
    Application();

    void Start(int argc, char** argv);
    void Run();

  private:
    State m_State;
    std::unique_ptr<Scene> m_ScenePtr;
    GeometryProcessing m_GeometryProcessing;
    Rasterization m_Rasterization;
    Screen m_Screen;

    void SetupScene(char** argv);
    void HandleInput();             // Handles the input
    void RenderScene();             // Handles the rendering pipeline
  };
  
}

#endif
