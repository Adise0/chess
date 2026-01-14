#pragma once
#include "../../types/vector2/Vector2.h"
#include "../../ui/elements/Draggable/Draggable.h"
#include "../types/Types.h"
#include <vector>

namespace Chess::Game {

using namespace Rendering::Elements;


class Piece {
public:
  /// @brief The current piece position
  Vector2Int position;
  /// @brief The type of the piece
  PieceType pieceType;
  /// @brief The team of the piece
  TEAM team;
  /// @brief The underlying Draggable element
  Draggable *element;

  /// @brief check if rooks or kings have moved
  bool hasMoved = false;

  /// @brief This piece's legal moves
  std::vector<Vector2Int> legalMoves;

public:
  Piece(Vector2Int startPosition, PieceType pieceType, TEAM team);
  Piece();
  ~Piece();


private:
  /// @brief Creates the visual element
  void CreateElement();

  /// @brief Gets the piece sprite
  /// @return The sprite corresponding to this piece type
  std::string GetPieceSprite();
};
} // namespace Chess::Game
