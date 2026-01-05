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

enum PieceType { // Mamon has escrit piece malament a tot arreu
  Pawn,
  Rook,
  Knight,
  Bishop,
  Queen,
  King
};

/// @brief The pice tteam (0 For Black, 1 for White)
typedef short TEAM;

class Pice {
public:
  /// @brief The current pice position
  POSITION position;
  /// @brief The type of the pice
  PieceType piceType;
  /// @brief The team of the pice
  TEAM team;
  /// @brief The underlying button element
  Button *element;

public:
  Pice(POSITION startPosition, PieceType piceType, TEAM team);

  /// @brief Gets the legal moves of this pice
  /// @param board The board
  /// @return A vector of the avialbale movees
  std::vector<POSITION> GetLegalMoves();


private:
  /// @brief Gets the pice sprite
  /// @return The sprite corresponding to this pice type
  const char *GetPiceSprite();
};
} // namespace Chess::Game
