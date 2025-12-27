#include "Rectangle.h"

namespace Chess::Rendering::Elements {

bool Rectangle::IsWithinRect(int x, int y) {
  // #region IsWithinRect
  if (x < rect.x) return false;
  if (x > rect.x + rect.w) return false;
  if (y < rect.y) return false;
  if (y > rect.y + rect.h) return false;
  return true;
  // #endregion
}

void Rectangle::SetPosition(int x, int y) {
  // #region SetPosition
  rect.x = x;
  rect.y = y;
  // #endregion
}

} // namespace Chess::Rendering::Elements
