#include "Board.h"
#include "../../gameManager/GameManager.h"
#include "../../ui/elements/rectangle/Rectangle.h"
#include "../../windowManager/WindowManager.h"

namespace Chess::Game {

using namespace Rendering;



TEAM Board::GetTurn() { return 0; }

POSITION Board::ToScreenPosition(POSITION boardPosition) {
  return {(short)(boardPosition.x * WindowManager::piceX),
          (short)(boardPosition.y * WindowManager::piceY)};
}
} // namespace Chess::Game
