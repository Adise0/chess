#pragma once
#include "../../ui/elements/button/Button.h"
#include "../types/Types.h"
#include <vector>

namespace Chess::Game {

using namespace Rendering::Elements;


class Piece {
public:
  /// @brief The current piece position
  POSITION position;
  /// @brief The type of the piece
  PieceType pieceType;
  /// @brief The team of the piece
  TEAM team;
  /// @brief The underlying button element
  Button *element;

public:
  Piece(POSITION startPosition, PieceType pieceType, TEAM team);

  /// @brief Gets the legal moves of this piece
  /// @param board The board
  /// @return A vector of the avialbale movees
  std::vector<POSITION> GetLegalMoves();


private:
  /// @brief Gets the piece sprite
  /// @return The sprite corresponding to this piece type
  std::string GetPieceSprite();
};
} // namespace Chess::Game
