#pragma once
#include "../../ui/elements/rectangle/Rectangle.h"
#include "../pice/Pice.h"
#include <vector>

namespace Chess::Game {
using namespace Rendering;
class Board {
public:
  /// @brief The current board pices
  std::vector<Pice *> pices;

private:
  /// @brief The current turn
  TEAM currrentTurn;

  Rectangle *t;

public:
  Board();

  /// @brief Gets the currennt turn
  /// @return Whether the current turnn is black or white
  TEAM GetTurn();

  /// @brief Transforms a board position to a screen position
  /// @param boardPosition The board position to transform
  /// @return The transformed screen position
  POSITION ToScreenPosition(POSITION boardPosition);
};
} // namespace Chess::Game
