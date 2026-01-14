#pragma once
#include "../../ui/elements/rectangle/Rectangle.h"
#include "../piece/Piece.h"
#include "../types/Types.h"
#include <optional>
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
  /// @brief The top padding of the board
  static constexpr short topPadding = 20;

  /// @brief The board array
  Piece *board[boardSize][boardSize]{nullptr};
  Piece *selectedPiece;

private:
  /// @brief The current turn
  TEAM currentTurn;

  std::vector<Element *> currentLegalMoveShowers;

  Piece *kings[2];

public:
  /// @brief Constructor
  Board();

  /// @brief Gets the currennt turn
  /// @return Whether the current turnn is black or white
  TEAM GetTurn();

  /// @brief Gets the legal moves of a piece
  /// @param piece The piece to get moves for
  /// @return A vector of legal moves
  std::vector<Vector2Int> GetLegalMoves(Piece *piece);

  /// @brief Requests for a piece to move to a target position
  /// @param piece The piece to move
  /// @param target The target position
  /// @return Whether the move could be done
  bool RequestMove(Piece *piece, Vector2Int target);

private:
  /// @brief Populates the board
  void PopulateBoard();

  /// @brief Configures a piece
  /// @param piece The piece to configure
  void ConfigurePiece(Piece *piece);


  /// @brief Shows the legal moves of the passed piece
  /// @param piece The piece to show the legal moves for
  void ShowLegalMoves(Piece *piece);

  /// @brief Hides the legal moves
  void HideLegalMoves();

  /// @brief Starts a turn
  void StartTurn();

  /// @brief Checks if a move is legal
  /// @param piece The piece that wants to move
  /// @param target The target square
  /// @return Whether it is fully legal
  bool IsMoveLegal(Piece *piece, Vector2Int target);

  /// @brief Checks if a king is in check
  /// @param team The team of the king
  /// @return Whether that king is in check
  bool IsKingInCheck(TEAM team);

  /// @brief Caluclates and shows a piece's currrent legal moves
  /// @param piece The piece to calculate moves for
  // void CalculateLegalMoves(Piece *piece);

  /// @brief Gets the pawn legal moves
  /// @param piece The pawn piece
  /// @return The legal moves
  std::vector<Vector2Int> GetPawnLegalMoves(Piece *piece);

  /// @brief Gets the legal moves for a rook
  /// @param piece The rook piece
  /// @return The legal moves
  std::vector<Vector2Int> GetRookLegalMoves(Piece *piece);


  /// @brief Gets the legal moves for a bishop
  /// @param piece The bishop piece
  /// @return The legal moves
  std::vector<Vector2Int> GetBishopLegalMoves(Piece *piece);

  /// @brief Gets the knight legal moves
  /// @param piece The kinght piece
  /// @return The legal moves
  std::vector<Vector2Int> GetKnightLegalMoves(Piece *piece);

  /// @brief Gets the queen legal moves
  /// @param piece The queen piece
  /// @return The legal moves
  std::vector<Vector2Int> GetQueenLegalMoves(Piece *piece);

  /// @brief Gets the king legal moves
  /// @param piece The king piece
  /// @return The legal moves
  std::vector<Vector2Int> GetKingLegalMoves(Piece *piece);


  /// @brief Gets the legal moves for a line
  /// @param startPosition The starting position of the line
  /// @param direction The direction of the line
  /// @param piece The piece to check the line for
  /// @param limit The limit of moves to check OR -1 for no limit
  /// @return The legal moves
  std::vector<Vector2Int> GetLineLegalMoves(Vector2 startPosition, Vector2 direction, Piece *piece,
                                            short limit = -1);
  std::vector<Vector2Int> GetLineLegalMoves(Vector2 startPosition, Vector2 direction, Piece *piece,
                                            std::optional<Piece *> &firstEnemy);
  std::vector<Vector2Int> GetLineLegalMoves(Vector2 startPosition, Vector2 direction, Piece *piece,
                                            short limit, std::optional<Piece *> &firstEnemy);

  /// @brief Gets the legal moves for a diagonal
  /// @param startPosition The starting position of the diagonal
  /// @param direction The direction of the diagonal
  /// @param piece The piece to check the diagonal for
  /// @param limit The limit of moves to check OR -1 for no limit
  /// @return The legal moves
  std::vector<Vector2Int> GetDiagonalLegalMoves(Vector2 startPosition, Vector2 direction,
                                                Piece *piece, short limit = -1);
  std::vector<Vector2Int> GetDiagonalLegalMoves(Vector2 startPosition, Vector2 direction,
                                                Piece *piece, std::optional<Piece *> &firstEnemy);
  std::vector<Vector2Int> GetDiagonalLegalMoves(Vector2 startPosition, Vector2 direction,
                                                Piece *piece, short limit,
                                                std::optional<Piece *> &firstEnemy);
  /// @brief Checks if a move is valid and adds it to the moves vector
  /// @param move The move to check
  /// @param moves The legal moves vector
  /// @return Whether the move is legal
  bool CheckMove(Vector2Int move, std::vector<Vector2Int> &moves);

  bool EnsureLegal(Vector2Int targetTile, Vector2Int originalTile, Piece *piece);
};
} // namespace Chess::Game
