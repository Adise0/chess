#include "SupersayanPawn.h"
#include "../../../gameManager/GameManager.h"
#include "../../../windowManager/WindowManager.h"

namespace Chess::Rendering::Screens {

void SupersayanPawn::Load() {
  // #region Load

  Vector2 bgPos =
      Vector2(WindowManager::resolutionX / 2 - 120 / 2, WindowManager::resolutionY / 2 - 120 / 2);
  SDL_FRect backgroundRect = {bgPos.x, bgPos.y, 120, 120};

  short offset = (120 - 100) / 2;
  float knightX = bgPos.x + offset;
  float knightY = bgPos.y + offset;

  float bishopX = bgPos.x + offset + 50;
  float bishopY = bgPos.y + offset;

  float rookX = bgPos.x + offset;
  float rookY = bgPos.y + offset + 50;

  float queenX = bgPos.x + offset + 50;
  float queenY = bgPos.y + offset + 50;

  Renderer backgroundRenderer({255, 255, 255, 255}, -1);
  background = new Rectangle(backgroundRect, backgroundRenderer);
  screenElements.push_back(background);

  SDL_Texture *knightButtonTexture =
      WindowManager::LoadSprite("assets/sprites/pieces/whiteKnight.png");
  SDL_FRect knightButtonRect = {knightX, knightY, 50, 50};
  Renderer KnightButtonRenderer(knightButtonTexture, NULL, NULL, 2);
  knightButton = new Button(knightButtonRect, KnightButtonRenderer);

  SDL_Texture *bishopButtonTexture =
      WindowManager::LoadSprite("assets/sprites/pieces/whiteBishop.png");
  SDL_FRect bishopButtonRect = {bishopX, bishopY, 50, 50};
  Renderer bishopButtonRenderer(bishopButtonTexture, NULL, NULL, 2);
  bishopButton = new Button(bishopButtonRect, bishopButtonRenderer);

  SDL_Texture *rookButtonTexture = WindowManager::LoadSprite("assets/sprites/pieces/blackRook.png");
  SDL_FRect rookButtonRect = {rookX, rookY, 50, 50};
  Renderer rookButtonRenderer(rookButtonTexture, NULL, NULL, 2);
  rookButton = new Button(rookButtonRect, rookButtonRenderer);

  SDL_Texture *queenButtonTexture =
      WindowManager::LoadSprite("assets/sprites/pieces/blackQueen.png");
  SDL_FRect queenButtonRect = {queenX, queenY, 50, 50};
  Renderer queenButtonRenderer(queenButtonTexture, NULL, NULL, 2);
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
