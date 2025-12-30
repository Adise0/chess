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
#include <vector>
#include <windows.h>
namespace Chess {

using namespace Rendering;
using namespace Elements;
using namespace Screens;

bool GameManager::isRunning = false;
MainMenu GameManager::mainMenu = MainMenu();

void GameManager::ProcessInput(SDL_Event &event) {
  // #region ProcessInput
  while (SDL_PollEvent(&event)) {

    switch (event.type) {
    case SDL_EVENT_QUIT:
      isRunning = false;
      break;

    default:
      for (Screen *screen : Screen::screens) {
        if (!screen->isPresented) continue;
        std::vector<Element *> sceeenElements = screen->GetElementsToRender();
        for (Element *element : sceeenElements) {
          element->HandleEvent(event);
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
  SDL_SetRenderDrawColor(WindowManager::renderer, 0, 100, 80, 255);
  SDL_RenderClear(WindowManager::renderer);

  MessageBoxA(nullptr, "asdsad" + Screen::screens.size(), "Runtime error", MB_OK | MB_ICONERROR);
  for (Screen *screen : Screen::screens) {
    if (!screen->isPresented) continue;
    std::vector<Element *> sceeenElements = screen->GetElementsToRender();
    for (Element *element : sceeenElements) {
      element->Render();
    }
  }



  SDL_RenderPresent(WindowManager::renderer);
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

void GameManager::LoadScreens() {
  for (Screen *screen : Screen::screens) {
    screen->Load();
  }
}

} // namespace Chess

