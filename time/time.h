#ifndef TIME_H
#define TIME_H

#include <chrono>

namespace engine {

  class Time {
  public:
    Time() = delete;

    // Getters
    static float GetDeltaTime();
    static float GetTimeSinceLastFrame();

    static void UpdateDeltaTime();

  private:
    static std::chrono::high_resolution_clock::time_point s_LastFrameTime, s_PreviousFrameTime;
    static std::chrono::duration<float> s_DeltaTime;
  };
  
}

#endif
