#pragma once

namespace Chess::Game {
/// @brief Defines a position
typedef struct POSITION {
  /// @brief The x
  short x;
  /// @brief The y
  short y;
} POSITION;

enum PieceType { Pawn, Rook, Knight, Bishop, Queen, King };

/// @brief The piece team (0 For Black, 1 for White)
typedef short TEAM;
} // namespace Chess::Game
