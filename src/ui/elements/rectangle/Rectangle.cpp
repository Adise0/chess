#include "Rectangle.h"
#include <SDL3/SDL.h>
#include <windows.h>
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
  SDL_SetRenderDrawColor(WindowManager::renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(WindowManager::renderer, &rect);

  if (renderer.baseImage != nullptr) {
    SDL_RenderTexture(WindowManager::renderer, renderer.baseImage, nullptr, &rect);
  }
};



} // namespace Chess::Rendering::Elements
