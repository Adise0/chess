#include "GameManager.h"
#include "../windowManager/WindowManager.h"
#include <chrono>

namespace Chess {

using namespace Rendering;

bool GameManager::isRunning = false;

void GameManager::ProcessInput(SDL_Event &event) {
  // #region ProcessInput
  while (SDL_PollEvent(&event)) {

    switch (event.type) {
    case SDL_EVENT_QUIT:
      isRunning = false;
      break;
    }
  }
  // #endregion
}

void GameManager::Update(float deltaTime) {
  // #region Update

  // #endregion
}

void GameManager::Render() {
  // #region Render
  SDL_SetRenderDrawColor(WindowManager::renderer, 0, 100, 80, 255);
  SDL_RenderClear(WindowManager::renderer);
  SDL_RenderPresent(WindowManager::renderer);
  // #endregion
}


void GameManager::Run() {
  // #region Run
  isRunning = true;

  SDL_Event event;
  auto lastFrame = std::chrono::high_resolution_clock::now();


  while (isRunning) {
    ProcessInput(event);
    auto thisFrame = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(thisFrame - lastFrame).count();
    lastFrame = thisFrame;

    Update(deltaTime);
    Render();
  }
  // #endregion
}

} // namespace Chess

