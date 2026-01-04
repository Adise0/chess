#include "InGame.h"

#include "../../../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
#include <iostream>
namespace Chess::Rendering::Screens {



void InGame::Load() {
  // #region Load

  SDL_FRect backgroundRect = {0, 0, WindowManager::resolutionX, WindowManager::resolutionY};
  Renderer backgroundRenderer({118, 150, 86, 1});
  background = new Rectangle(backgroundRect, backgroundRenderer);
  screenElements.push_back(background);

  SDL_FRect rect = {0, 0, 50, 50};
  Renderer rend({255, 0, 0, 255});
  Rectangle *t = new Rectangle(rect, rend);
  screenElements.push_back(t);

  board = new Board();

  // #endregion
}

void InGame::PresentInt() {
  // #region PresentInt
  // Nothing to load onPresent
  // #endregion
}


std::vector<Element *> InGame::GetElementsToRender() {
  // #region GetElementsToRender
  return screenElements;
  // #endregion
}


} // namespace Chess::Rendering::Screens
