#include "Board.h"
#include "../../gameManager/GameManager.h"
#include "../../windowManager/WindowManager.h"

namespace Chess::Game {



Board::Board() {
  // SDL_FRect rect = {200, 200, 150, 150};
  // Renderer rend({255, 0, 0, 255});
  // t = new Rectangle(rect, rend);

  float xPosition = 275;
  float yPosition = 50;
  float squareWidth = 90.0f;
  float squareHeight = 90.0f;

  Renderer light({240, 217, 181, 255});
  Renderer dark({181, 136, 99, 255});

  for (int i = 0; i < 8; i++) {
    xPosition = 275;
    for (int j = 0; j < 8; j++) {
      SDL_FRect rect = {xPosition, yPosition, squareWidth, squareHeight};

      if (i % 2 == 0) {
        if (j % 2 == 0) {
          Rectangle *square = new Rectangle(rect, light);
          GameManager::inGame.AppendElement(square);
        } else if (j % 2 == 1) {
          Rectangle *square = new Rectangle(rect, dark);
          GameManager::inGame.AppendElement(square);
        }
      }

      else {
        if (j % 2 == 0) {
          Rectangle *square = new Rectangle(rect, dark);
          GameManager::inGame.AppendElement(square);
        } else if (j % 2 == 1) {
          Rectangle *square = new Rectangle(rect, light);
          GameManager::inGame.AppendElement(square);
        }
      }
      xPosition += squareWidth;
    }
    yPosition += squareHeight;
  }


  // GameManager::inGame.AppendElement(t);
}

TEAM Board::GetTurn() { return currrentTurn; }

POSITION Board::ToScreenPosition(POSITION boardPosition) {
  return {(short)(boardPosition.x * WindowManager::piceX),
          (short)(boardPosition.y * WindowManager::piceY)};
}
} // namespace Chess::Game
