#include "Board.h"
#include "../../gameManager/GameManager.h"
#include "../../windowManager/WindowManager.h"
#include <algorithm>
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

      Renderer *renderer;
      if (row % 2 == 0) {
        if (col % 2 == 0) renderer = &lightTileRenderer;
        else renderer = &darkTileRenderer;
      } else {
        if (col % 2 == 0) renderer = &darkTileRenderer;
        else renderer = &lightTileRenderer;
      }

      CreateTile(tileRect, *renderer);
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

void Board::CreateTile(SDL_FRect rect, Renderer renderer) {
  // #region CreateTile
  Rectangle *createdTile = new Rectangle(rect, renderer);
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


  return {(short)(boardPosition.x * tileSize + offsetX),
          (short)(boardPosition.y * tileSize + offsetY)};
  // #endregion
}

POSITION Board::GetClosestTile(float x, float y) {
  // #region GetClosestTile
  float offsetX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  float offsetY = BOARD_PADDING;

  float offsetedX = x - offsetX;
  float offsetedY = y - offsetY;

  float boardX = (offsetedX / tileSize);
  float boardY = (offsetedY / tileSize);

  int row = (int)std::lround(boardX);
  int col = (int)std::lround(boardY);

  row = std::clamp(row, 0, boardSize - 1);
  col = std::clamp(col, 0, boardSize - 1);


  return {(short)row, (short)col};
  // #endregion
};

void Board::SetPiecePosition(POSITION boardPosition) {
  // #region SetPiecePosition
  Piece *piece = board[boardPosition.x][boardPosition.y];
  if (!piece) return;
  POSITION screenPosition = ToScreenPosition(boardPosition);

  piece->element->SetPosition(screenPosition.x, screenPosition.y);
  // #endregion
}
} // namespace Chess::Game
