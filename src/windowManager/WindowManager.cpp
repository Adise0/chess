#include "WindowManager.h"
#include <stdexcept>

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

namespace Chess::Rendering {

SDL_Renderer *WindowManager::renderer = nullptr;
SDL_Window *WindowManager::window = nullptr;
bool WindowManager::isRunning = false;

void WindowManager::CreateChessWindow() {
  // #region CreateChessWindow
  if (!SDL_Init(SDL_INIT_VIDEO))
    throw std::runtime_error("Failed to initialize SDL video subsystem");

  window = SDL_CreateWindow("Chess", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0);
  if (!window) throw std::runtime_error("Failed to create SDL window");

  renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) throw std::runtime_error("Failed to create SDL renderer");

  isRunning = true;
  RunWindow();
  // #endregion
}

void WindowManager::RunWindow() {
  // #region RunWindow
  SDL_Event event;
  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        isRunning = false;
        break;

      default:
        break;
      }
    }
  }

  //TEMP
  SDL_SetRenderDrawColor(renderer, 0, 40, 80, 255);
  SDL_RenderClear(renderer);

  //TODO: Draw here

  SDL_RenderPresent(renderer);
  //ENDTEMP

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
