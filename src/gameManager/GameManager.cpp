#include "GameManager.h"
#include "../ui/button/Button.h"
#include "../ui/element/Element.h"
#include "../ui/rectangle/Rectangle.h"
#include "../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <chrono>
#include <iostream>
#include <string>

namespace Chess {

using namespace Rendering;
using namespace Elements;

bool GameManager::isRunning = false;
SDL_Texture *GameManager::backgroundTexture = nullptr;

void GameManager::ProcessInput(SDL_Event &event) {
  // #region ProcessInput
  while (SDL_PollEvent(&event)) {

    switch (event.type) {
    case SDL_EVENT_QUIT:
      isRunning = false;
      break;

    default:
      for (Element *element : Element::elements) {
        element->HandleEvent(event);
      }
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

  if (GameManager::backgroundTexture) {
    SDL_FRect srect{0, 0, 860, 537};
    SDL_FRect rrect{0, 0, 860, 537};
    SDL_RenderTexture(WindowManager::renderer, GameManager::backgroundTexture, &srect, &rrect);
  }
  for (Element *element : Element::elements) {
    element->Render();
  }


  SDL_RenderPresent(WindowManager::renderer);
  // #endregion
}

void GameManager::Run() {
  // #region Run
  SDL_Texture *testTexture =
      IMG_LoadTexture(WindowManager::renderer, "assets/sprites/playButton.png");

  SDL_FRect rect3{300, 200, 50, 50};
  SDL_Color col{100, 255, 255, 255};
  Elements::Button bigAssButton(rect3, testTexture);



  GameManager::backgroundTexture =
      IMG_LoadTexture(WindowManager::renderer, "assets/sprites/BackgroundForChess.png");

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

