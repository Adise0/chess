#pragma once
#include "../../elements/button/Button.h"
#include "../../elements/rectangle/Rectangle.h"
#include "../screen/Screen.h"
#include <SDL3/SDL.h>

namespace Chess::Rendering::Screens {
using namespace Elements;

class MainMenu : public Screen {

private:
  /// @brief The background image
  Rectangle *background;

  /// @brief The play button
  Button *playButton;

public:
  MainMenu() : Screen() {};
  /// @brief Main menu set up (background, button, on click button starts game)
  void Load() override;

  /// @brief Stores element pointers
  /// @return
  virtual std::vector<Element *> GetElementsToRender() override;

private:
  void PresentInt() override;
};
} // namespace Chess::Rendering::Screens
