#include "../../elements/element/Element.h"
#include <vector>



namespace Chess::Rendering::Screens {
using namespace Elements;
class Screen {

public:
  /// @brief The screen store
  static std::vector<Screen *> screens;

  /// @brief Registers a screen to the store
  /// @param screen The screen to register
  static void RegisterScreen(Screen *screen);

  /// @brief Unregisters a screen from the store
  /// @param screen The screen to unregister
  static void UnregisterScreen(Screen *screen);

private:
  std::vector<Element> screenElements;

public:
  bool isPresented;

public:
  Screen();
  void Present(bool present);

protected:
  virtual void PresentInt();
};
} // namespace Chess::Rendering::Screens