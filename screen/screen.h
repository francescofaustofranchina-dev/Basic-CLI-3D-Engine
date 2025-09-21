#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

namespace engine {

  class Screen {
  public:
    Screen(int width, int height);

    // Setters
    void SetWidth(int width);
    void SetHeight(int height);
    void SetScreenPixel(int row, int col, char val);

    // Getters
    int GetWidth() const;
    int GetHeight() const;
    float GetAspectRatio() const;
        
    bool IsPixelValid(int x, int y) const;
    void ClearScreen();
    void PrintScreen() const;

  private:
    int m_Width, m_Height;
    std::vector<char> m_ScreenMat;
  };
  
}

#endif
