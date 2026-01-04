#include "Board.h"
#include "../../gameManager/GameManager.h"
#include "../../windowManager/WindowManager.h"

namespace Chess::Game {



Board::Board() {
  SDL_FRect rect = {200, 200, 150, 150};
  Renderer rend({255, 0, 0, 255});
  t = new Rectangle(rect, rend);

  GameManager::inGame.AppendElement(t);
}

TEAM Board::GetTurn() { return currrentTurn; }

POSITION Board::ToScreenPosition(POSITION boardPosition) {
  return {(short)(boardPosition.x * WindowManager::piceX),
          (short)(boardPosition.y * WindowManager::piceY)};
}
} // namespace Chess::Game
