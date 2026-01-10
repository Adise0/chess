#include "InGame.h"

#include "../../../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
#include <iostream>
namespace Chess::Rendering::Screens {



void InGame::Load() {
  // #region Load
  SDL_FRect backgroundRect = {0, 0, WindowManager::resolutionX, WindowManager::resolutionY};
  Renderer backgroundRenderer({48, 46, 43, 1}, -2);
  background = new Rectangle(backgroundRect, backgroundRenderer);
  screenElements.push_back(background);

  board = new Board();
  // #endregion
}

std::vector<Element *> InGame::GetElementsToRender() {
  // #region GetElementsToRender
  return screenElements;
  // #endregion
}

void InGame::PieceMovement() {

  for (Element *square : screenElements) {
  };
}


} // namespace Chess::Rendering::Screens
