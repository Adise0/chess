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
  AppendElement(background);

  ConstructBoard();

  board = new Board();
  // #endregion
}

void InGame::Update() {
  // if (!board || !board->lastMovedPiece) return;

  // SDL_Color dark = {181, 136, 99, 255};
  // SDL_Color light = {240, 217, 181, 255};
  // SDL_Color yellow = {250, 235, 146, 255};

  // for (short i = 0; i < Board::boardSize; i++) {
  //   for (short j = 0; j < Board::boardSize; j++) {

  //     if (i == board->lastMovedPiece->position.x && j == board->lastMovedPiece->position.y) {
  //       tiles[i][j]->baseColor = yellow;
  //     } else {
  //       if (i % 2 == 0) {
  //         if (j % 2 == 0) tiles[i][j]->baseColor = light;
  //         else tiles[i][j]->baseColor = dark;
  //       } else {
  //         if (j % 2 == 0) tiles[i][j]->baseColor = dark;
  //         else tiles[i][j]->baseColor = light;
  //       }
  //     }
  //   }
  // }
}



std::vector<Element *> InGame::GetElementsToRender() {
  // #region GetElementsToRender
  return screenElements;
  // #endregion
}

void InGame::ConstructBoard() {
  // #region ConstructBoard
  int initialX = (WindowManager::resolutionX / 2) - (Board::boardSize / 2 * Board::tileSize);
  int initialY = Board::topPadding;
  int currentX = initialX;
  int currentY = initialY;

  Renderer lightTileRenderer({240, 217, 181, 255}, -1);
  Renderer darkTileRenderer({181, 136, 99, 255}, -1);


  for (short col = 0; col < Board::boardSize; col++) {
    currentY = initialY;
    for (short row = 0; row < Board::boardSize; row++) {
      SDL_FRect tileRect = {currentX, currentY, Board::tileSize, Board::tileSize};

      Renderer *renderer;
      if (row % 2 == 0) {
        if (col % 2 == 0) renderer = &lightTileRenderer;
        else renderer = &darkTileRenderer;
      } else {
        if (col % 2 == 0) renderer = &darkTileRenderer;
        else renderer = &lightTileRenderer;
      }

      CreateTile(col, row, tileRect, *renderer);

      currentY += Board::tileSize;
    }
    currentX += Board::tileSize;
  }

  // #endregion
}

void InGame::CreateTile(short x, short y, SDL_FRect rect, Renderer renderer) {
  // #region CreateTile
  Button *createdTile = new Button(rect, renderer);
  // createdTile->OnClick([this, x, y] {
  //   if (!board || !board->selectedPiece) return;

  //   bool moved = board->RequestMove(board->selectedPiece, Vector2Int(x, y));
  //   Vector2 screenPos = Board::ToScreenPosition(board->selectedPiece->position);
  //   board->selectedPiece->element->SetPosition(screenPos.x, screenPos.y);
  //   if (moved) board->lastMovedPiece = board->selectedPiece;

  //   // board->selectedPiece = nullptr;
  // });
  tiles[x][y] = createdTile;
  AppendElement(createdTile);
  // #endregion
}

} // namespace Chess::Rendering::Screens
