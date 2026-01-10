#include "GameManager.h"
#include "../ui/elements/button/Button.h"
#include "../ui/elements/element/Element.h"
#include "../ui/elements/rectangle/Rectangle.h"
#include "../ui/screens/screen/Screen.h"
#include "../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <windows.h>
namespace Chess {

using namespace Rendering;
using namespace Elements;
using namespace Rendering::Screens;

bool GameManager::isRunning = false;
MainMenu GameManager::mainMenu = MainMenu();
InGame GameManager::inGame = InGame();

void GameManager::ProcessInput(SDL_Event &event) {
  // #region ProcessInput
  while (SDL_PollEvent(&event)) {

    switch (event.type) {
    case SDL_EVENT_QUIT:
      isRunning = false;
      break;

    default:
      for (Screen *screen : Screen::GetScreens()) {
        if (!screen->isPresented) continue;
        std::vector<Element *> sceenElements = screen->GetElementsToRender();
        std::stable_sort(sceenElements.begin(), sceenElements.end(),
                         [](const Element *a, const Element *b) {
                           return a->renderer.sortingLayer > b->renderer.sortingLayer;
                         });

        for (Element *element : sceenElements) {
          // element->HandleEvent(event);
          if (element->HandleEvent(event)) break;
        }
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
  SDL_RenderClear(WindowManager::renderer);

  for (Screen *screen : Screen::GetScreens()) {
    if (!screen->isPresented) continue;
    std::vector<Element *> elements = screen->GetElementsToRender();

    SortElements(elements);

    for (Element *e : elements) {
      e->Render();
    }
  }

  SDL_RenderPresent(WindowManager::renderer);
  // #endregion
}

void GameManager::SortElements(std::vector<Element *> &elements) {
  // #region SortElements
  std::stable_sort(elements.begin(), elements.end(), [](const Element *a, const Element *b) {
    return a->renderer.sortingLayer < b->renderer.sortingLayer;
  });
  // #endregion
}

void GameManager::LoadScreens() {
  // #region LoadScreens
  for (Screen *screen : Screen::GetScreens()) {
    screen->Load();
  }
  // #endregion
}

void GameManager::Run() {
  // #region Run
  LoadScreens();
  mainMenu.Present(true);

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

void GameManager::StartGame() {
  // #region StartGame
  mainMenu.Present(false);
  inGame.Present(true);
  // #endregion
}


} // namespace Chess

