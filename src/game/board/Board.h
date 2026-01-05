#pragma once
#include "../../ui/elements/rectangle/Rectangle.h"
#include "../pice/Pice.h"
#include <vector>

namespace Chess::Game {
using namespace Rendering;
class Board {
public:
  /// @brief The size of the board in tiles
  static constexpr short boardSize = 8;
  /// @brief The size of a pice in pixels
  static constexpr short piceSize = 70;
  /// @brief The size of a tile in pixels
  static constexpr short tileSize = 90;

public:
  /// @brief The current board pices
  std::vector<Pice *> pices;
  /// @brief The board array
  Pice *board[boardSize][boardSize];

private:
  /// @brief The current turn
  TEAM currrentTurn;

public:
  Board();

  /// @brief Gets the currennt turn
  /// @return Whether the current turnn is black or white
  TEAM GetTurn();

  /// @brief Transforms a board position to a screen position
  /// @param boardPosition The board position to transform
  /// @return The transformed screen position
  POSITION ToScreenPosition(POSITION boardPosition);

  void ConstructBoard();

  void CreateTile(SDL_FRect rect, Renderer renderer);
};
} // namespace Chess::Game
