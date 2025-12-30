#include "Screen.h"
#include <stdexcept>

namespace Chess::Rendering::Screens {

std::vector<Screen *> Screen::screens;

void Screen::RegisterScreen(Screen *screen) {
  // #region RegisterScreen
  screens.push_back(screen);
  // #endregion
}
void Screen::UnregisterScreen(Screen *screen) {

  auto foundScreenIterator = std::find(screens.begin(), screens.end(), screen);

  if (foundScreenIterator != screens.end()) {
    screens.erase(foundScreenIterator);
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
  throw std::runtime_error("Get elemennts not implemented");
}

}; // namespace Chess::Rendering::Screens
