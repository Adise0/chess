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


  bool softDeleted;

protected:
  /// @brief Whether the element is color-based
  bool hasColor;

public:
  /// @brief Renders the element
  virtual void Render();

  /// @brief Handles the element events
  /// @param event The current event
  virtual void HandleEvent(SDL_Event &event);

  /// @brief Runs every frame
  virtual void Update(float deltaTime);

  /// @brief Creates a new element
  Element();
};
} // namespace Chess::Rendering::Elements
