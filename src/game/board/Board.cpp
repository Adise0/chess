#include "Board.h"
#include "../../gameManager/GameManager.h"
#include "../../windowManager/WindowManager.h"

namespace Chess::Game {

#define BOARD_PADDING 20


Board::Board() { ConstructBoard(); }

void Board::ConstructBoard() {
  // #region ConstructBoard
  int initialX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  int initialY = BOARD_PADDING;
  int currentX = initialX;
  int currentY = initialY;

  Renderer lightTileRenderer({240, 217, 181, 255});
  Renderer darkTileRenderer({181, 136, 99, 255});


  for (size_t row = 0; row < boardSize; row++) {
    currentX = initialX;
    for (size_t col = 0; col < boardSize; col++) {
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
      currentX += tileSize;
    }
    currentY += tileSize;
  }

  // #endregion
}


void Board::CreateTile(SDL_FRect rect, Renderer renderer) {
  // #region CreateTile
  Rectangle *createdTile = new Rectangle(rect, renderer);
  GameManager::inGame.AppendElement(createdTile);
  // #endregion
}

TEAM Board::GetTurn() { return currrentTurn; }

POSITION Board::ToScreenPosition(POSITION boardPosition) {
  return {(short)(boardPosition.x * tileSize), (short)(boardPosition.y * tileSize)};
}
} // namespace Chess::Game
