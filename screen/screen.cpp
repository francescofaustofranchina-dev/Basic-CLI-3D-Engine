#include "screen.h"

#include <iostream>
#include <stdexcept>
#include <string>

namespace engine {
    
  Screen::Screen(int width, int height) {
    if (width <= 0 || height <= 0) {
      throw std::invalid_argument("EXCEPTION: screen width and height must be greater than 0");
    }

    m_Width = width;
    m_Height = height;
    m_ScreenMat.resize(static_cast<std::size_t>(m_Width * m_Height), ' ');
  }

  void Screen::SetWidth(int width) {
    if (width <= 0) {
      throw std::invalid_argument("EXCEPTION: screen width must be greater than 0");
    }

    m_Width = width;
    m_ScreenMat.resize(static_cast<std::size_t>(m_Width * m_Height), ' ');
  }

  void Screen::SetHeight(int height) {
    if (height <= 0) {
      throw std::invalid_argument("EXCEPTION: screen height must be greater than 0");
    }

    m_Height = height;
    m_ScreenMat.resize(static_cast<std::size_t>(m_Width * m_Height), ' ');
  }

  // REMEMBER: in order to keep this function safe, IsPixelValid() must be performed already
  void Screen::SetScreenPixel(int row, int col, char val) {
    m_ScreenMat[row * m_Width + col] = val;
  }

  int Screen::GetWidth() const { return m_Width; }

  int Screen::GetHeight() const { return m_Height; }

  float Screen::GetAspectRatio() const { return static_cast<float>(m_Width) / m_Height; }

  // Returns a value that indicates whether a pixel is inside the screen or not
  bool Screen::IsPixelValid(int row, int col) const {
    return row >= 0 && col >= 0 && row < m_Height && col < m_Width;
  }

  void Screen::ClearScreen() {
    std::fill(m_ScreenMat.begin(), m_ScreenMat.end(), ' ');
  }

  void Screen::PrintScreen() const {
    std::string output;
    output.reserve((2 * m_Width + 1) * m_Height + 10);  // Adds some chars for escape and margin
    output.append("\033[H\033[2J");                     // Clears the terminal

    std::size_t w = static_cast<std::size_t>(m_Width);
    std::size_t h = static_cast<std::size_t>(m_Height);

    for (std::size_t i{0}; i < h; ++i) {
      for (std::size_t j{0}; j < w; ++j) {
        char c = m_ScreenMat[i * w + j];
        output.push_back(c);
        output.push_back(c);
      }
      output.push_back('\n');
    }

    std::cout << output;
  }
  
}
