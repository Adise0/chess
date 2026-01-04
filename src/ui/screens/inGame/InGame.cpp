#include "InGame.h"
#include "../../../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
namespace Chess::Rendering::Screens {



void InGame::Load() {
  // #region Load

  SDL_FRect backgroundRect = {0, 0, WindowManager::resolutionX, WindowManager::resolutionY};
  SDL_Color backgroundColor = {118, 150, 86, 1};
  Renderer backgroundRenderer(&backgroundColor);
  background = new Rectangle(backgroundRect, backgroundRenderer);
  screenElements.push_back(background);
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
