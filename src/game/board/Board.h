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
  Pice *board[boardSize][boardSize]{
      // #region Initial array
      new Pice({0, 0}, PieceType::Rook, 0),
      new Pice({1, 0}, PieceType::Knight, 0),
      new Pice({2, 0}, PieceType::Bishop, 0),
      new Pice({3, 0}, PieceType::Queen, 0),
      new Pice({4, 0}, PieceType::King, 0),
      new Pice({5, 0}, PieceType::Bishop, 0),
      new Pice({6, 0}, PieceType::Knight, 0),
      new Pice({7, 0}, PieceType::Rook, 0),
      new Pice({0, 1}, PieceType::Pawn, 0),
      new Pice({1, 1}, PieceType::Pawn, 0),
      new Pice({2, 1}, PieceType::Pawn, 0),
      new Pice({3, 1}, PieceType::Pawn, 0),
      new Pice({4, 1}, PieceType::Pawn, 0),
      new Pice({5, 1}, PieceType::Pawn, 0),
      new Pice({6, 1}, PieceType::Pawn, 0),
      new Pice({7, 1}, PieceType::Pawn, 0),
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      new Pice({0, 6}, PieceType::Pawn, 1),
      new Pice({1, 6}, PieceType::Pawn, 1),
      new Pice({2, 6}, PieceType::Pawn, 1),
      new Pice({3, 6}, PieceType::Pawn, 1),
      new Pice({4, 6}, PieceType::Pawn, 1),
      new Pice({5, 6}, PieceType::Pawn, 1),
      new Pice({6, 6}, PieceType::Pawn, 1),
      new Pice({7, 6}, PieceType::Pawn, 1),
      new Pice({0, 7}, PieceType::Rook, 1),
      new Pice({1, 7}, PieceType::Knight, 1),
      new Pice({2, 7}, PieceType::Bishop, 1),
      new Pice({3, 7}, PieceType::Queen, 1),
      new Pice({4, 7}, PieceType::King, 1),
      new Pice({5, 7}, PieceType::Bishop, 1),
      new Pice({6, 7}, PieceType::Knight, 1),
      new Pice({7, 7}, PieceType::Rook, 1),
      // #endregion
  };

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

  void SetPicePosition(POSITION boardPosition);
};
} // namespace Chess::Game
