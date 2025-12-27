#include "GameManager.h"
#include "../ui/element/Element.h"
#include "../ui/rectangle/Rectangle.h"
#include "../windowManager/WindowManager.h"
#include <chrono>
#include <string>
#include <windows.h>

namespace Chess {

using namespace Rendering;
using namespace Elements;

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

  for (Element *element : Element::elements) {
    element->Render();
  }


  SDL_RenderPresent(WindowManager::renderer);
  // #endregion
}


void GameManager::Run() {
  // #region Run

  SDL_FRect rect = {50, 50, 50, 50};
  SDL_Color col = {255, 165, 0, 255};
  Elements::Rectangle testRectangle(rect, col);

  SDL_FRect rect2 = {100, 100, 50, 300};
  SDL_Color col2 = {100, 165, 100, 255};
  Elements::Rectangle testRectangle2(rect2, col2);

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

