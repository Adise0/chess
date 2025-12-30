#include "GameManager.h"
#include "../ui/board/board.h"
#include "../ui/button/Button.h"
#include "../ui/element/Element.h"
#include "../ui/rectangle/Rectangle.h"
#include "../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

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
    SDL_RenderTexture(WindowManager::renderer, GameManager::backgroundTexture, NULL, NULL);
  }

  for (Element *element : Element::elements) {
    element->Render();
  }

  SDL_RenderPresent(WindowManager::renderer);
  // #endregion
}

void GameManager::Run() {
  // #region Run

  GameManager::backgroundTexture =
      WindowManager::LoadSprite("assets/sprites/BackgroundForChess.png");


  SDL_Texture *baseTexture =
      IMG_LoadTexture(WindowManager::renderer, "assets/sprites/playButton.png");
  SDL_Texture *pressedTexture =
      IMG_LoadTexture(WindowManager::renderer, "assets/sprites/playButton_pressed.png");

  SDL_FRect rect3{300, 200, 50, 50};
  Renderer renderer(NULL, baseTexture, NULL, pressedTexture);
  Elements::Button *bigAssButton = new Button(rect3, renderer);


  bigAssButton->OnClick([bigAssButton, baseTexture] {
    SDL_DestroyTexture(GameManager::backgroundTexture);
    delete bigAssButton;
  });


  isRunning = true;
  SDL_Event event;
  auto lastFrame = std::chrono::high_resolution_clock::now();


  while (isRunning) {
    ProcessInput(event);
    auto thisFrame = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(thisFrame - lastFrame).count();
    lastFrame = thisFrame;

    // if (bigAssButton.deleteBackground == true) { // Add the board cretion function here
    //   SDL_DestroyTexture(GameManager::backgroundTexture);
    //   auto it = find(Element::elements.begin(), Element::elements.end(), &bigAssButton);
    //   if (it != Element::elements.end()) {
    //     Element::elements.erase(it);
    //     new ChessBoard();
    //   }
    // };

    // SDL_FRect rect = {300, 300, 100.0f, 100.0f};
    // SDL_Color currentColor = {200, 200, 200, 200};
    // Renderer renderer(&currentColor, nullptr, nullptr, nullptr);
    // Rectangle *testRectangle = new Rectangle(rect, renderer);
    // Element::elements.push_back(testRectangle);

    Update(deltaTime);
    Render();
  }
  // #endregion
}

} // namespace Chess

