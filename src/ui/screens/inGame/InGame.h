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

  Board *board;

public:
  InGame() : Screen() {};
  void Load() override;
  virtual std::vector<Element *> GetElementsToRender() override;

private:
  void PresentInt() override;
};
} // namespace Chess::Rendering::Screens
