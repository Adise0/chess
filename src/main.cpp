#include "window.h"
#include <iostream>

int main() {

  std::cout << "Creating window\n";

  Window *pWindow = new Window();

  bool running = true;

  while (running) {

    if (!pWindow->ProcessMessages()) {
      std::cout << "Closing";
      running = false;
    }

    Sleep(10);
  }

  delete pWindow;
}