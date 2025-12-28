#include "Rectangle.h"

namespace Chess::Rendering::Elements {

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

void Rectangle::Render() {
  // #region Render
  if (texture == nullptr) {
    SDL_SetRenderDrawColor(WindowManager::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(WindowManager::renderer, &rect);
    return;
  }

  else
    SDL_RenderTexture(WindowManager::renderer, texture, &rect, &rect);
  // #endregion
}

} // namespace Chess::Rendering::Elements
