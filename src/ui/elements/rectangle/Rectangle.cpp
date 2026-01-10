#include "Rectangle.h"
#include "../button/Button.h"
#include <windows.h>
namespace Chess::Rendering::Elements {

Rectangle::Rectangle(SDL_FRect rect, Renderer renderer) : Element() {
  // #region Rectangle
  this->rect = rect;
  this->renderer = renderer;

  if (renderer.baseImage) hasColor = false;
  else hasColor = true;
  // #endregion
}

Rectangle::Rectangle(SDL_FRect rect, Renderer renderer, Button *button) : Element() {
  // #region Rectangle
  this->rect = rect;
  this->renderer = renderer;
  this->button = button;

  if (renderer.baseImage) hasColor = false;
  else hasColor = true;
  // #endregion
}

bool Rectangle::IsWithinRect(float x, float y) {
  // #region IsWithinRect
  if (x < rect.x) return false;
  if (x > rect.x + rect.w) return false;
  if (y < rect.y) return false;
  if (y > rect.y + rect.h) return false;
  return true;
  // #endregion
}

void Rectangle::SetPosition(float x, float y) {
  // #region SetPosition
  rect.x = x;
  rect.y = y;
  // #endregion
}
} // namespace Chess::Rendering::Elements
