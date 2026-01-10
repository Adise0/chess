#pragma once
#include "../../ui/elements/rectangle/Rectangle.h"
#include "../piece/Piece.h"
#include <vector>

namespace Chess::Game {
using namespace Rendering;
class Board {
public:
  /// @brief The size of the board in tiles
  static constexpr short boardSize = 8;
  /// @brief The size of a piece in pixels
  static constexpr short pieceSize = 70;
  /// @brief The size of a tile in pixels
  static constexpr short tileSize = 90;

public:
  /// @brief The board array
  Piece *board[boardSize][boardSize]{
      // #region Initial array
      {
          new Piece({0, 0}, PieceType::Rook, 0),
          new Piece({0, 1}, PieceType::Pawn, 0),
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          new Piece({0, 6}, PieceType::Pawn, 1),
          new Piece({0, 7}, PieceType::Rook, 1),
      },
      {
          new Piece({1, 0}, PieceType::Knight, 0),
          new Piece({1, 1}, PieceType::Pawn, 0),
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          new Piece({1, 6}, PieceType::Pawn, 1),
          new Piece({1, 7}, PieceType::Knight, 1),
      },
      {
          new Piece({2, 0}, PieceType::Bishop, 0),
          new Piece({2, 1}, PieceType::Pawn, 0),
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          new Piece({2, 6}, PieceType::Pawn, 1),
          new Piece({2, 7}, PieceType::Bishop, 1),
      },
      {
          new Piece({3, 0}, PieceType::Queen, 0),
          new Piece({3, 1}, PieceType::Pawn, 0),
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          new Piece({3, 6}, PieceType::Pawn, 1),
          new Piece({3, 7}, PieceType::Queen, 1),
      },
      {
          new Piece({4, 0}, PieceType::King, 0),
          new Piece({4, 1}, PieceType::Pawn, 0),
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          new Piece({4, 6}, PieceType::Pawn, 1),
          new Piece({4, 7}, PieceType::King, 1),
      },
      {
          new Piece({5, 0}, PieceType::Bishop, 0),
          new Piece({5, 1}, PieceType::Pawn, 0),
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          new Piece({5, 6}, PieceType::Pawn, 1),
          new Piece({5, 7}, PieceType::Bishop, 1),
      },
      {
          new Piece({6, 0}, PieceType::Knight, 0),
          new Piece({6, 1}, PieceType::Pawn, 0),
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          new Piece({6, 6}, PieceType::Pawn, 1),
          new Piece({6, 7}, PieceType::Knight, 1),
      },
      {
          new Piece({7, 0}, PieceType::Rook, 0),
          new Piece({7, 1}, PieceType::Pawn, 0),
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          new Piece({7, 6}, PieceType::Pawn, 1),
          new Piece({7, 7}, PieceType::Rook, 1),
      },
      // #endregion
  };


private:
  /// @brief The current turn
  TEAM currrentTurn;

public:
  /// @brief Constructor
  Board();

  /// @brief Gets the currennt turn
  /// @return Whether the current turnn is black or white
  TEAM GetTurn();


  /// @brief Transforms a board position to a screen position
  /// @param boardPosition The board position to transform
  /// @return The transformed screen position
  POSITION ToScreenPosition(POSITION boardPosition);

  /// @brief Creates the board
  void ConstructBoard();

  /// @brief Creates a square
  /// @param rect x, y, width, height
  /// @param renderer a renderer
  void CreateTile(SDL_FRect rect, Renderer renderer, Button *button, short row, short col);

  /// @brief Sets the position of a piece in ints
  /// @param boardPosition The board position to "atach" to the piece
  void SetPiecePosition(POSITION boardPosition);
};
} // namespace Chess::Game
