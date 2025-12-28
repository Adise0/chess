#include "Renderer.h"
#include "../../windowManager/WindowManager.h"
#include <stdexcept>


namespace Chess::Rendering {

void Renderer::Render(Texture textureType, SDL_FRect rect) {
  // #region Render
  SDL_Texture *texture;


  if (textureType == Texture::color) {
    SDL_SetRenderDrawColor(WindowManager::renderer, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(WindowManager::renderer, &rect);
    return;
  }

  switch (textureType) {
  case Texture::base:
    texture = baseImage;
    break;
  case Texture::hover:
    texture = hoverImage;
    break;
  case Texture::pressed:
    texture = pressedImage;
    break;
  default:
    throw std::runtime_error("Render texture not found");
    break;
  }


  SDL_RenderTexture(WindowManager::renderer, texture, NULL, &rect);
  // #endregion
}
} // namespace Chess::Rendering
