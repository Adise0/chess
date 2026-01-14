#pragma once
#include "../../elements/button/Button.h"
#include "../../elements/rectangle/Rectangle.h"
#include "../screen/Screen.h"
#include <SDL3/SDL.h>

namespace Chess::Rendering::Screens {
using namespace Elements;

class SupersayanPawn : public Screen {

private:
  /// @brief The background image
  Rectangle *background;

  Button *knightButton;
  Button *bishopButton;
  Button *rookButton;
  Button *queenButton;

public:
  // Vector2 position;



public:
  /// @brief Creates the main menu screen
  SupersayanPawn() : Screen() {};

  /// @brief Loads the screen
  void Load() override;

  /// @brief Getter for the elements to render
  /// @return The vector of elements to render this frame
  virtual std::vector<Element *> GetElementsToRender() override;
};
} // namespace Chess::Rendering::Screens
