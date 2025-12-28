#include "WindowManager.h"
#include <iostream>

#define DEFAULT_WINDOW_WIDTH 860
#define DEFAULT_WINDOW_HEIGHT 537

namespace Chess::Rendering {

SDL_Window *WindowManager::window = nullptr;
SDL_Renderer *WindowManager::renderer = nullptr;


void WindowManager::InitializeWindow() {
  // #region InitializeWindow
  if (!SDL_Init(SDL_INIT_VIDEO))
    throw std::runtime_error("Failed to initialize SDL video subsystem");

  window = SDL_CreateWindow("Chess", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0);
  if (!window) throw std::runtime_error("Failed to create SDL window");

  renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) throw std::runtime_error("Failed to create SDL renderer");
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
