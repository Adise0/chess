#include "WindowManager.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>


namespace Chess::Rendering {

SDL_Window *WindowManager::window = nullptr;
SDL_Renderer *WindowManager::renderer = nullptr;

const short WindowManager::resolutionX = 1280;
const short WindowManager::resolutionY = 800;
const short WindowManager::piceX = 50;
const short WindowManager::piceY = 50;



void WindowManager::InitializeWindow() {
  // #region InitializeWindow
  if (!SDL_Init(SDL_INIT_VIDEO))
    throw std::runtime_error("Failed to initialize SDL video subsystem");

  window = SDL_CreateWindow("Chess", resolutionX, resolutionY, 0);
  if (!window) throw std::runtime_error("Failed to create SDL window");

  renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) throw std::runtime_error("Failed to create SDL renderer");
  // #endregion
}

SDL_Texture *WindowManager::LoadSprite(const char *spritePath) {
  // #region LoadSprite
  SDL_Texture *texture = IMG_LoadTexture(renderer, spritePath);
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  return texture;
  // #endregion
}

void WindowManager::Dispose() {
  // #region Dispose
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }

  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }

  SDL_Quit();
  // #endregion
}
} // namespace Chess::Rendering
