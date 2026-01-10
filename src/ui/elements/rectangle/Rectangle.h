#pragma once
#include "../../../windowManager/WindowManager.h"
#include "../../renderer/Renderer.h"
#include "../element/Element.h"
#include <SDL3/SDL.h>

namespace Chess::Rendering::Elements {

class Button;

class Rectangle : public Element {


public:
  /// @brief Creates a new rectangle with a texture
  /// @param rect The rect to use
  /// @param renderer The renderer to use
  Rectangle(SDL_FRect rect, Renderer renderer);

  /// @param button The button to use
  Rectangle(SDL_FRect rect, Renderer renderer, Button *button);
  Button *button = nullptr;

public:
  /// @brief Sets the position of the rectangle
  /// @param x The new x
  /// @param y The new y
  void SetPosition(float x, float y);

protected:
  /// @brief Checks if the position is within the rectangle
  /// @param x The x coord
  /// @param y The y coord
  /// @return Whether it is inside the rectangle
  bool IsWithinRect(float x, float y);
};
} // namespace Chess::Rendering::Elements
