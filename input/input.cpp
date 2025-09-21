#include "input.h"

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

// DISCLAIMER: this code has been entirely made by an LLM

namespace engine {
  
  bool kbhit() {
    timeval tv{0, 0};
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    return select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv) > 0;
  }

  char getch() {
    termios oldt{}, newt{};
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
  }
  
}
