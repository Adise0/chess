#pragma once
#include "../pice/Pice.h"
#include <vector>

namespace Chess::Game {

class Board {
public:
  /// @brief The current board pices
  std::vector<Pice *> pices;

private:
  /// @brief The current turn
  TEAM currrentTurn;

public:
  Board();

  /// @brief Gets the currennt turn
  /// @return Whether the current turnn is black or white
  TEAM GetTurn();

  /// @brief Transforms a board position to a screen position
  /// @param boardPosition The booard position to transform
  /// @return The transformed screen position
  POSITION ToScreenPosition(POSITION boardPosition);
};
} // namespace Chess::Game
