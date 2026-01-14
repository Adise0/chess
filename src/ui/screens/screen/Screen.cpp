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
  // #region UnregisterScreen
  auto foundScreenIterator = std::find(GetScreens().begin(), GetScreens().end(), screen);

  if (foundScreenIterator != GetScreens().end()) {
    GetScreens().erase(foundScreenIterator);
  }
  // #endregion
}


Screen::Screen() {
  // #region Screen
  isPresented = false;
  RegisterScreen(this);
  // #endregion
}

std::vector<Screen *> &Screen::GetScreens() {
  // #region GetScreens
  static std::vector<Screen *> instance;
  return instance;
  // #endregion
};

void Screen::Present(bool present) {
  // #region Present
  if (!isPresented && present) {
    isPresented = true;
    OnPresent();
  }
  if (isPresented && !present) isPresented = false;
  // #endregion
}

void Screen::OnPresent() {}

void Screen::Load() {
  // #region Load
  throw std::runtime_error("Screen load not implemented");
  // #endregion
}

void Screen::Update() {}

std::vector<Element *> Screen::GetElementsToRender() {
  // #region GetElementsToRender
  throw std::runtime_error("Get elements not implemented");
  // #endregion
}

void Screen::AppendElement(Element *element) {
  // #region AppendElement
  screenElements.push_back(element);
  // #endregion
}

void Screen::RemoveElement(Element *element) {
  // #region RemoveElement

  element->softDeleted = true;
  // #endregion
}

}; // namespace Chess::Rendering::Screens
