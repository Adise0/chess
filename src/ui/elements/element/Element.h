#pragma once
#include "../../renderer/Renderer.h"
#include <SDL3/SDL.h>
#include <vector>

namespace Chess::Rendering::Elements {
class Element {

public:
  /// @brief The rect
  SDL_FRect rect;

  /// @brief The element renderer
  Renderer renderer;

public:
  /// @brief Renders the element
  virtual void Render();

  /// @brief Handles the element events
  /// @param event The current event
  virtual void HandleEvent(SDL_Event &event);


  Element();
};
} // namespace Chess::Rendering::Elements
