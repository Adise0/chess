#include "MainMenu.h"
#include "../../../gameManager/GameManager.h"
#include "../../../windowManager/WindowManager.h"

namespace Chess::Rendering::Screens {

void MainMenu::Load() {
  // #region Load
  SDL_Texture *backgroundTexture =
      WindowManager::LoadSprite("assets/sprites/BackgroundForChess.png");

  SDL_FRect backgroundRect = {0, 0, WindowManager::resolutionX, WindowManager::resolutionY};

  Renderer backgroundRenderer(backgroundTexture, NULL, NULL, -2);
  background = new Rectangle(backgroundRect, backgroundRenderer);
  screenElements.push_back(background);

  SDL_Texture *basePlayButtonTexture = WindowManager::LoadSprite("assets/sprites/playButton.png");
  SDL_Texture *pressedPlayButtonTexture =
      WindowManager::LoadSprite("assets/sprites/playButton_pressed.png");

  SDL_FRect playButtonRect = {300, 200, 50, 50};
  Renderer playButtonRenderer(basePlayButtonTexture, NULL, pressedPlayButtonTexture);
  playButton = new Button(playButtonRect, playButtonRenderer);

  playButton->OnClick([] { GameManager::StartGame(); });

  screenElements.push_back(playButton);

  std::cout << "Presenting screen: " << typeid(*this).name() << "\n";
  std::cout << "Main Menu Presented\n";
  std::cout << playButton->boardCol << "\n" << playButton->boardRow << "\n";
  // #endregion
}

std::vector<Element *> MainMenu::GetElementsToRender() {
  // #region GetElementsToRender
  return screenElements;
  // #endregion
}

} // namespace Chess::Rendering::Screens
