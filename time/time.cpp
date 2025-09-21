#include "time.h"

#include "settings.h"

namespace engine {

  std::chrono::high_resolution_clock::time_point Time::s_LastFrameTime;
  std::chrono::high_resolution_clock::time_point Time::s_PreviousFrameTime;
  std::chrono::duration<float> Time::s_DeltaTime;

  float Time::GetDeltaTime() {
    return s_DeltaTime.count();
  }

  float Time::GetTimeSinceLastFrame() {
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<float>(now - s_LastFrameTime).count();
  }

  void Time::UpdateDeltaTime() {
    auto now = std::chrono::high_resolution_clock::now();

    if (s_LastFrameTime == std::chrono::high_resolution_clock::time_point{}) {
      s_LastFrameTime = now;
      s_PreviousFrameTime = now;  

      s_DeltaTime = std::chrono::duration<float>(g_TargetFrameTime);
    }
    else {
      s_PreviousFrameTime = s_LastFrameTime;
      s_LastFrameTime = now;        
        
      s_DeltaTime = std::chrono::duration<float>(s_LastFrameTime - s_PreviousFrameTime);
    }
  }
  
}
