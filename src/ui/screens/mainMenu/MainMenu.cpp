#include "MainMenu.h"
#include "../../../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
namespace Chess::Rendering::Screens {



void MainMenu::Load() {
  // #region Load
  SDL_Texture *backgroundTexture =
      WindowManager::LoadSprite("assets/sprites/BackgroundForChess.png");

  SDL_FRect backgroundRect = {0, 0, WindowManager::resolutionX, WindowManager::resolutionY};

  Renderer backgroundRenderer(NULL, backgroundTexture);
  background = new Rectangle(backgroundRect, backgroundRenderer);
  screenElements.push_back(background);



  SDL_Texture *basePlayButtonTexture = WindowManager::LoadSprite("assets/sprites/playButton.png");
  SDL_Texture *pressedPlayButtonTexture =
      WindowManager::LoadSprite("assets/sprites/playButton_pressed.png");

  SDL_FRect playButtonRect = {300, 200, 50, 50};
  Renderer playButtonRenderer(NULL, basePlayButtonTexture, NULL, pressedPlayButtonTexture);
  playButton = new Button(playButtonRect, playButtonRenderer);
  screenElements.push_back(playButton);
  // #endregion
}

void MainMenu::PresentInt() {
  // #region PresentInt
  // Nothing to load onPresent
  // #endregion
}


std::vector<Element *> MainMenu::GetElementsToRender() {
  // #region GetElementsToRender
  return screenElements;
  // #endregion
}


} // namespace Chess::Rendering::Screens
