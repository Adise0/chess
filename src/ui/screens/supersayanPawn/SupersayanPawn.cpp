#include "SupersayanPawn.h"
#include "../../../gameManager/GameManager.h"
#include "../../../windowManager/WindowManager.h"

namespace Chess::Rendering::Screens {

void SupersayanPawn::Load() {
  // #region Load
  SDL_Texture *backgroundTexture =
      WindowManager::LoadSprite("assets/sprites/BackgroundForChess.png");

  SDL_FRect backgroundRect = {0, 0, WindowManager::resolutionX, WindowManager::resolutionY};

  Renderer backgroundRenderer(backgroundTexture, NULL, NULL, -2);
  background = new Rectangle(backgroundRect, backgroundRenderer);
  screenElements.push_back(background);

  SDL_Texture *knightButtonTexture = WindowManager::LoadSprite("assets/sprites/playButton.png");
  SDL_FRect knightButtonRect = {0, 0, 50, 50};
  Renderer KnightButtonRenderer(knightButtonTexture);
  knightButton = new Button(knightButtonRect, KnightButtonRenderer);

  SDL_Texture *bishopButtonTexture = WindowManager::LoadSprite("assets/sprites/playButton.png");
  SDL_FRect bishopButtonRect = {0, 0, 50, 50};
  Renderer bishopButtonRenderer(bishopButtonTexture);
  bishopButton = new Button(bishopButtonRect, bishopButtonRenderer);

  SDL_Texture *rookButtonTexture = WindowManager::LoadSprite("assets/sprites/playButton.png");
  SDL_FRect rookButtonRect = {0, 0, 50, 50};
  Renderer rookButtonRenderer(rookButtonTexture);
  rookButton = new Button(rookButtonRect, rookButtonRenderer);

  SDL_Texture *queenButtonTexture = WindowManager::LoadSprite("assets/sprites/playButton.png");
  SDL_FRect queenButtonRect = {0, 0, 50, 50};
  Renderer queenButtonRenderer(queenButtonTexture);
  queenButton = new Button(queenButtonRect, queenButtonRenderer);



  screenElements.push_back(knightButton);
  screenElements.push_back(bishopButton);
  screenElements.push_back(rookButton);
  screenElements.push_back(queenButton);
  // #endregion
}

std::vector<Element *> SupersayanPawn::GetElementsToRender() {
  // #region GetElementsToRender
  return screenElements;
  // #endregion
}
} // namespace Chess::Rendering::Screens
