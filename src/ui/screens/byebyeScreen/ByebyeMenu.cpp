#include "ByebyeMenu.h"
#include "../../../gameManager/GameManager.h"
#include "../../../windowManager/WindowManager.h"

namespace Chess::Rendering::Screens {

void ByebyeMenu::Load() {
  // #region Load
  SDL_Texture *backgroundTexture = WindowManager::LoadSprite("assets/sprites/STALE-MATE.png");

  SDL_FRect backgroundRect = {0, 0, WindowManager::resolutionX, WindowManager::resolutionY};

  Renderer backgroundRenderer(backgroundTexture, NULL, NULL, -2);
  background = new Rectangle(backgroundRect, backgroundRenderer);
  screenElements.push_back(background);

  // #endregion
}

std::vector<Element *> ByebyeMenu::GetElementsToRender() {
  // #region GetElementsToRender
  return screenElements;
  // #endregion
}
} // namespace Chess::Rendering::Screens
