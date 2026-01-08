#pragma once
#include "../../../game/board/Board.h"
#include "../../elements/button/Button.h"
#include "../../elements/rectangle/Rectangle.h"
#include "../screen/Screen.h"

namespace Chess::Rendering::Screens {
using namespace Elements;
using namespace Game;
class InGame : public Screen {

private:
  /// @brief The background rectangle
  Rectangle *background;
  /// @brief The board
  Board *board;

public:
  /// @brief Creates the in game screen
  InGame() : Screen() {};

  /// @brief Loads the screen
  void Load() override;

  /// @brief Getter for the elements to render
  /// @return The vector of elements to render this frame
  virtual std::vector<Element *> GetElementsToRender() override;
};
} // namespace Chess::Rendering::Screens
