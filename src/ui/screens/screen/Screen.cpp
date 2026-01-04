#include "Screen.h"
#include <Windows.h>
#include <iostream>
#include <string>

namespace Chess::Rendering::Screens {


void Screen::RegisterScreen(Screen *screen) {
  // #region RegisterScreen
  GetScreens().push_back(screen);
  // #endregion
}
void Screen::UnregisterScreen(Screen *screen) {

  auto foundScreenIterator = std::find(GetScreens().begin(), GetScreens().end(), screen);

  if (foundScreenIterator != GetScreens().end()) {
    GetScreens().erase(foundScreenIterator);
  }
}


Screen::Screen() {
  isPresented = false;
  RegisterScreen(this);
}

void Screen::Present(bool present) {
  if (!isPresented && present) {
    isPresented = true;
    PresentInt();
  }
  if (isPresented && !present) isPresented = false;
}

void Screen::PresentInt() { throw std::runtime_error("Screen present not implemented"); }
void Screen::Load() { throw std::runtime_error("Screen load not implemented"); }
std::vector<Element *> Screen::GetElementsToRender() {
  throw std::runtime_error("Get elements not implemented");
}

void Screen::AppendElement(Element *element) { screenElements.push_back(element); }

}; // namespace Chess::Rendering::Screens
