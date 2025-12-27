#pragma once
#include "../../windowManager/WindowManager.h"
#include "../element/Element.h"
#include <SDL3/SDL.h>

namespace Chess::Rendering::Elements {

class Rectangle : public Element {

public:
  /// @brief The base color
  SDL_Color color;
  /// @brief The rect
  SDL_FRect rect;

public:
  /// @brief Creates a new rectangle
  /// @param rect The rect to use
  Rectangle(SDL_FRect rect, SDL_Color color) : rect(rect), color(color) {}

  /// @brief Sets the position of the rectangle
  /// @param x The new x
  /// @param y The new y
  void SetPosition(int x, int y);

  void Render() override;

private:
  /// @brief Checks if the position is within the rectangle
  /// @param x The x coord
  /// @param y The y coord
  /// @return Whether it is inside the rectangle
  bool IsWithinRect(int x, int y);
};
} // namespace Chess::Rendering::Elements
