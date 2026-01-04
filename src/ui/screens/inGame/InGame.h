#pragma once
#include "../../elements/button/Button.h"
#include "../../elements/rectangle/Rectangle.h"
#include "../screen/Screen.h"

namespace Chess::Rendering::Screens {
using namespace Elements;

class InGame : public Screen {

private:
  /// @brief The background rectangle
  Rectangle *background;


public:
  InGame() : Screen() {};
  void Load() override;
  virtual std::vector<Element *> GetElementsToRender() override;

private:
  void PresentInt() override;
};
} // namespace Chess::Rendering::Screens
