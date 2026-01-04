#include "Rectangle.h"
#include <windows.h>
namespace Chess::Rendering::Elements {

Rectangle::Rectangle(SDL_FRect rect, Renderer renderer) : Element() {
  this->rect = rect;
  this->renderer = renderer;
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
