#include "application.h"

#include "entity/camera/camera.h"
#include "entity/light/directional_light.h"
#include "entity/object3d/object3d.h"
#include "input/input.h"
#include "parser/parser.h"
#include "time/time.h"
#include "settings.h"

#include <iostream>
#include <stdexcept>

// REMEMBER: y-axis orientation is from top to bottom (y-)
// REMEMBER: z-axis orientation is from back to front (z-)

namespace engine {

  Application::Application() : 
    m_State{State::Ready},
    m_ScenePtr{nullptr},
    m_Screen{g_HorizontalRes, g_VerticalRes},
    m_GeometryProcessing{m_Screen}, 
    m_Rasterization{m_Screen} 
  {}

  void Application::Start(int argc, char** argv) {
    m_State = State::Starting;

    if (argc != 2) {
      throw std::invalid_argument("ERROR: invalid number of arguments. Expected 2, got " + std::to_string(argc));
    }

    SetupScene(argv);
  }

  void Application::Run() {
    m_State = State::Running;

    while (m_State == State::Running) {
      Time::UpdateDeltaTime();

      HandleInput();
      RenderScene();
    } 
  }

  void Application::SetupScene(char** argv) {
    m_ScenePtr = std::make_unique<Scene>(
      Object3D{Parser::LoadMeshFromFile(argv[1])},
      Camera{g_FovDeg, g_ZNear, g_ZFar},
      DirectionalLight{1.0f}
    );

    m_ScenePtr->camera.GetTransform().SetPosition(Vector3{0.0f, -2.0f, -6.0f});
    m_ScenePtr->directionalLight.GetTransform().SetRotation(Vector3{0.0f, 180.0f, 0.0f}); // TO-DO: analyze the rotation's behavior
  }

  void Application::HandleInput() {
    bool isAnyKeyBeenPressed{kbhit()};

    if (isAnyKeyBeenPressed) {
      char key{static_cast<char>(tolower(getch()))};
            
      if (key == 't') {
        m_State = State::Shutting;
      }
    }
  }

  void Application::RenderScene() {    
    m_Screen.ClearScreen();

    m_ScenePtr->object3D.GetTransform().ApplyRotation(
      Vector3{0.0f, 90.0f * Time::GetDeltaTime(), 0.0f}
    );

    m_Rasterization.RasterizeMesh(m_GeometryProcessing.GetProcessedMesh(*m_ScenePtr));
            
    m_Screen.PrintScreen();
  }
  
}
