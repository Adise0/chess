#pragma once
#include "../../elements/button/Button.h"
#include "../../elements/rectangle/Rectangle.h"
#include "../screen/Screen.h"
#include <SDL3/SDL.h>

namespace Chess::Rendering::Screens {
using namespace Elements;

class ByebyeMenu : public Screen {

public:
  /// @brief The background image
  Rectangle *background;


public:
  /// @brief Creates the main menu screen
  ByebyeMenu() : Screen() {};

  /// @brief Loads the screen
  void Load() override;

  /// @brief Getter for the elements to render
  /// @return The vector of elements to render this frame
  virtual std::vector<Element *> GetElementsToRender() override;
};
} // namespace Chess::Rendering::Screens
