#pragma once
#include "../../elements/element/Element.h"
#include <vector>



namespace Chess::Rendering::Screens {
using namespace Elements;
class Screen {

public:
  /// @brief The screen store
  static std::vector<Screen *> &GetScreens();

  /// @brief Registers a screen to the store
  /// @param screen The screen to register
  static void RegisterScreen(Screen *screen);

  /// @brief Unregisters a screen from the store
  /// @param screen The screen to unregister
  static void UnregisterScreen(Screen *screen);



public:
  /// @brief Checks if its presented or not
  bool isPresented;

public:
  /// @brief Creates a new screen
  Screen();

  /// @brief Sets whether the screen should be presented
  /// @param present Whether to present it
  void Present(bool present);

  /// @brief Loads the screen
  virtual void Load();

  /// @brief Getter for the elements to render
  /// @return The vector of elements to render this frame
  virtual std::vector<Element *> GetElementsToRender();

  /// @brief Appens an element to this screen
  /// @param element The element to append
  void AppendElement(Element *element);

protected:
  /// @brief The elements of this screen
  std::vector<Element *> screenElements;

  /// @brief Runs on every new present
  virtual void OnPresent();
};
} // namespace Chess::Rendering::Screens
