#pragma once
#include <SDL3/SDL.h>
#include <vector>

namespace Chess::Rendering::Elements {
class Element {

public:
  /// @brief The elements store
  static std::vector<Element *> elements;

  /// @brief Registers a UI element to the store
  /// @param element The element to register
  static void RegisterElement(Element *element);

  /// @brief Unregisters an elmenet from the store
  /// @param element The element to unregister
  static void UnregisterElement(Element *element);

public:
  /// @brief The rect
  SDL_FRect rect;

public:
  /// @brief Renders the element
  virtual void Render();

  /// @brief Handles the element events
  /// @param event The current event
  virtual void HandleEvent(SDL_Event &event);


  Element();
  virtual ~Element();
};
} // namespace Chess::Rendering::Elements
