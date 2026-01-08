#pragma once
#include "../../ui/elements/button/Button.h"
#include <vector>

namespace Chess::Game {

using namespace Rendering::Elements;

/// @brief Defines a position
typedef struct POSITION {
  /// @brief The x
  short x;
  /// @brief The y
  short y;
} POSITION;

enum PieceType { Pawn, Rook, Knight, Bishop, Queen, King };

/// @brief The piece tteam (0 For Black, 1 for White)
typedef short TEAM;

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
  const char *GetPieceSprite();

  /// @brief Creates the underlying visual element
  void CreateElement();
};
} // namespace Chess::Game
