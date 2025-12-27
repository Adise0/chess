#include "WindowManager.h"
#include <iostream>

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

namespace Chess::Rendering {

SDL_Window *WindowManager::window = nullptr;
SDL_Renderer *WindowManager::renderer = nullptr;


void WindowManager::InitializeWindow() {
  // #region InitializeWindow
  if (!SDL_Init(SDL_INIT_VIDEO))
    throw std::runtime_error("Failed to initialize SDL video subsystem");

  window =
      SDL_CreateWindow("Chess", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
  if (!window) throw std::runtime_error("Failed to create SDL window");

  renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) throw std::runtime_error("Failed to create SDL renderer");
  // #endregion
}

// void WindowManager::RunWindow() {
//   // #region RunWindow
//   SDL_Event event;

//   int g = 0;
//   while (isRunning) {
//     //Input
//     while (SDL_PollEvent(&event)) {
//       switch (event.type) {
//       case SDL_EVENT_QUIT:
//         isRunning = false;

//         break;

//       case SDL_EVENT_KEY_DOWN:
//         if (event.key.key == SDLK_E) {
//           g = rand() % 256;
//         }
//         break;

//       default:
//         break;
//       }
//     }

//     // Game logic

//     //Rendering

//     //TEMP
//     SDL_SetRenderDrawColor(renderer, 0, g, 80, 255);
//     SDL_RenderClear(renderer);
//     //ENDTEMP

//     SDL_RenderPresent(renderer);
//   }
//   // #endregion
// }

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
