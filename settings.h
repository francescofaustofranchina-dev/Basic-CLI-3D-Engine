#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstddef>

namespace engine {
  
  // Camera settings
  constexpr float g_FovDeg{90.0f};
  constexpr float g_ZNear{0.1f};
  constexpr float g_ZFar{1000.0f};

  // Screen settings
  constexpr size_t g_HorizontalRes{300}; // The actual horizontal pixel count is doubled
  constexpr size_t g_VerticalRes{300};

  // Frame rate limit settings (NOT APPLIED YET)
  constexpr float g_FrameRateLimit{60.0f};
  constexpr float g_TargetFrameTime{1.0f / g_FrameRateLimit};
  
}

#endif

