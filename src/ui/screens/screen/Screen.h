#pragma once
#include "../../elements/element/Element.h"
#include <vector>



namespace Chess::Rendering::Screens {
using namespace Elements;
class Screen {

public:
  /// @brief The screen store
  static std::vector<Screen *> &GetScreens() {
    static std::vector<Screen *> instance;
    return instance;
  };

  /// @brief Registers a screen to the store
  /// @param screen The screen to register
  static void RegisterScreen(Screen *screen);

  /// @brief Unregisters a screen from the store
  /// @param screen The screen to unregister
  static void UnregisterScreen(Screen *screen);



public:
  bool isPresented;

public:
  Screen();
  void Present(bool present);
  virtual void Load();
  virtual std::vector<Element *> GetElementsToRender();

protected:
  std::vector<Element *> screenElements;
  virtual void PresentInt();
};
} // namespace Chess::Rendering::Screens
