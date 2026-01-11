#pragma once
#include "../../ui/elements/rectangle/Rectangle.h"
#include "../piece/Piece.h"
#include "../types/Types.h"
#include <vector>

namespace Chess::Game {
using namespace Rendering;
class Board {
public:
  /// @brief Gets the closest tile to a screen position
  /// @param x The x position
  /// @param y The y position
  /// @return The closest tile position
  static Vector2Int GetClosestTile(Vector2 screenPosition);

  /// @brief Transforms a board position to a screen position
  /// @param boardPosition The board position to transform
  /// @return The transformed screen position
  static Vector2 ToScreenPosition(Vector2Int boardPosition);


public:
  /// @brief The size of the board in tiles
  static constexpr short boardSize = 8;
  /// @brief The size of a piece in pixels
  static constexpr short pieceSize = 70;
  /// @brief The size of a tile in pixels
  static constexpr short tileSize = 90;

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
  TEAM currentTurn;

  std::vector<Vector2Int> currentLegalMoves;
  std::vector<Element *> currentLegalMoveShowers;
  Piece *selectedPiece;

public:
  /// @brief Constructor
  Board();

  /// @brief Gets the currennt turn
  /// @return Whether the current turnn is black or white
  TEAM GetTurn();

  /// @brief Creates the board
  void ConstructBoard();

  /// @brief Creates a square
  /// @param rect x, y, width, height
  /// @param renderer a renderer
  void CreateTile(SDL_FRect rect, Renderer renderer);

  /// @brief Configures a piece
  /// @param boardPosition The board position to "atach" to the piece
  void ConfigurePiece(Vector2Int boardPosition);

  /// @brief Gets the legal moves of a piece
  /// @param piece The piece to get moves for
  /// @return A vector of legal moves
  std::vector<Vector2Int> GetLegalMoves(Piece *piece);

private:
  /// @brief Caluclates and shows a piece's currrent legal moves
  /// @param piece The piece to calculate moves for
  void CalculateLegalMoves(Piece *piece);

  /// @brief Gets the pawn legal moves
  /// @param piece The pawn piece
  /// @return The legal moves
  std::vector<Vector2Int> GetPawnLegalMoves(Piece *piece);

  /// @brief Gets the legal moves for a rook
  /// @param piece The rook piece
  /// @return The legal moves
  std::vector<Vector2Int> GetRookLegalMoves(Piece *piece);

  /// @brief Gets the knight legal moves
  /// @param piece The kinght piece
  /// @return The legal moves
  std::vector<Vector2Int> GetKnightLegalMoves(Piece *piece);

  /// @brief Gets the queen legal moves
  /// @param piece The queen piece
  /// @return The legal moves
  std::vector<Vector2Int> GetQueenLegalMoves(Piece *piece);


  std::vector<Vector2Int> GetBishopLegalMoves(Piece *piece);

  /// @brief Checks if a move is valid and adds it to the moves vector
  /// @param move The move to check
  /// @param moves The legal moves vector
  /// @return Whether the move is legal
  bool CheckMove(Vector2Int move, std::vector<Vector2Int> &moves);
};
} // namespace Chess::Game
