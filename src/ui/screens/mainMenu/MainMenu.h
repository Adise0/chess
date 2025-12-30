#pragma once
#include "../../elements/button/Button.h"
#include "../../elements/rectangle/Rectangle.h"
#include "../screen/Screen.h"

namespace Chess::Rendering::Screens {
using namespace Elements;

class MainMenu : public Screen {

private:
  /// @brief The background image
  Rectangle *background;

  /// @brief The play button
  Button *playButton;

public:
  MainMenu();
  void Load() override;
  virtual std::vector<Element *> GetElementsToRender() override;

private:
  void PresentInt() override;
};
} // namespace Chess::Rendering::Screens
