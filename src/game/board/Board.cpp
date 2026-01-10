#include "Board.h"
#include "../../gameManager/GameManager.h"
#include "../../ui/elements/button/Button.h"
#include "../../windowManager/WindowManager.h"
#include <iostream>
#include <string>

namespace Chess::Game {

#define BOARD_PADDING 20


Board::Board() {
  // #region Board
  ConstructBoard();
  // #endregion
}

void Board::ConstructBoard() {
  // #region ConstructBoard

  int initialX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  int initialY = BOARD_PADDING;
  int currentX = initialX;
  int currentY = initialY;

  Renderer lightTileRenderer({240, 217, 181, 255}, -1);
  Renderer darkTileRenderer({181, 136, 99, 255}, -1);


  for (size_t col = 0; col < boardSize; col++) {
    currentY = initialY;
    for (size_t row = 0; row < boardSize; row++) {
      SDL_FRect tileRect = {currentX, currentY, tileSize, tileSize};
      Button *button = new Button(tileRect, nullptr);
      Renderer *renderer;
      if (row % 2 == 0) {
        if (col % 2 == 0) renderer = &lightTileRenderer;
        else renderer = &darkTileRenderer;
      } else {
        if (col % 2 == 0) renderer = &darkTileRenderer;
        else renderer = &lightTileRenderer;
      }

      CreateTile(tileRect, *renderer, button);
      SetPiecePosition({
          (short)row,
          (short)col,
      });
      currentY += tileSize;
    }
    currentX += tileSize;
  }

  // #endregion
}

void Board::CreateTile(SDL_FRect rect, Renderer renderer, Button *button) {
  // #region CreateTile
  Rectangle *createdTile = new Rectangle(rect, renderer, button);
  GameManager::inGame.AppendElement(createdTile);
  // #endregion
}

TEAM Board::GetTurn() {
  // #region GetTurn
  return currrentTurn;
  // #endregion
}

POSITION Board::ToScreenPosition(POSITION boardPosition) {
  // #region ToScreenPosition
  float offsetX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  float offsetY = BOARD_PADDING;

  offsetX += (tileSize - pieceSize) / 2;
  offsetY += (tileSize - pieceSize) / 2;

  return {(short)(boardPosition.x * tileSize + offsetX),
          (short)(boardPosition.y * tileSize + offsetY)};
  // #endregion
}

void Board::SetPiecePosition(POSITION boardPosition) {
  // #region SetPiecePosition
  Piece *piece = board[boardPosition.x][boardPosition.y];
  if (!piece) return;
  POSITION screenPosition = ToScreenPosition(boardPosition);

  piece->element->SetPosition(screenPosition.x, screenPosition.y);
  // #endregion
}
} // namespace Chess::Game
