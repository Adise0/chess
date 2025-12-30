#include "../../elements/button/Button.h"
#include "../../elements/rectangle/Rectangle.h"
#include "../screen/Screen.h"

namespace Chess::Rendering::Screens {
using namespace Elements;

class MainMenu : public Screen {

public:
  MainMenu();

private:
  /// @brief The background image
  Rectangle background;

  /// @brief The play button
  Button playButton;
};
} // namespace Chess::Rendering::Screens
