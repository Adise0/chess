#include "Board.h"
#include "../../gameManager/GameManager.h"
#include "../../windowManager/WindowManager.h"
#include <algorithm>
#include <iostream>
#include <string>
#define NOMINMAX
#include <windows.h>


namespace Chess::Game {



Board::Board() {
  // #region Board


  PopulateBoard();

  currentTurn = 1;
  selectedPiece = nullptr;

  currentLegalMoveShowers.clear();

  StartTurn();
  // #endregion
}


void Board::PopulateBoard() {
  // #region PopulateBoard
  Piece *newBoard[boardSize][boardSize]{{
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
                                        }};


  for (short i = 0; i < boardSize; i++) {
    for (short j = 0; j < boardSize; j++) {
      if (board[i][j]) board[i][j] = nullptr;
      board[i][j] = newBoard[i][j];
      if (board[i][j]) ConfigurePiece(board[i][j]);
    }
  }
  // #endregion
}


TEAM Board::GetTurn() {
  // #region GetTurn
  return currentTurn;
  // #endregion
}

Vector2 Board::ToScreenPosition(Vector2Int boardPosition) {
  // #region ToScreenPosition
  float offsetX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  float offsetY = topPadding;


  return {boardPosition.x * tileSize + offsetX, boardPosition.y * tileSize + offsetY};
  // #endregion
}

Vector2Int Board::GetClosestTile(Vector2 screenPosition) {
  // #region GetClosestTile
  float offsetX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  float offsetY = topPadding;

  float offsetedX = screenPosition.x - offsetX;
  float offsetedY = screenPosition.y - offsetY;

  float boardX = (offsetedX / tileSize);
  float boardY = (offsetedY / tileSize);

  int row = (int)std::lround(boardX);
  int col = (int)std::lround(boardY);

  row = std::clamp(row, 0, boardSize - 1);
  col = std::clamp(col, 0, boardSize - 1);


  return {(short)row, (short)col};
  // #endregion
};


void Board::ConfigurePiece(Piece *piece) {
  // #region ConfigurePiece
  if (!piece) return;
  Vector2Int piecePosition = piece->position;
  Vector2Int screenPosition = ToScreenPosition(piecePosition);

  if (piece->pieceType == PieceType::King) kings[piece->team] = piece;
  piece->element->SetPosition(screenPosition.x, screenPosition.y);

  piece->element->OnClick([this, piece] {
    if (!piece || piece->team != currentTurn) return;
    selectedPiece = piece;
    ShowLegalMoves(piece);
  });
  piece->element->OnDragStart([this, piece] {
    if (!piece || piece->team != currentTurn) return;
    selectedPiece = piece;
    ShowLegalMoves(piece);
  });
  piece->element->OnDragEnd([this, piece](Vector2 dropPosition) {
    try {
      if (!piece) throw std::runtime_error("Piece missmatch");


      Vector2 tile = GetClosestTile(dropPosition);
      bool moved = RequestMove(piece, tile);
      Vector2 screenPos = ToScreenPosition(piece->position);
      piece->element->SetPosition(screenPos.x, screenPos.y);
      if (moved) lastMovedPiece = piece;

    } catch (const std::exception &e) {
      MessageBoxA(nullptr, e.what(), "Runtime error", MB_OK | MB_ICONERROR);
    } catch (...) {
      MessageBoxA(nullptr, "Unknown exception in onDrag end", "Runtime error",
                  MB_OK | MB_ICONERROR);
    }
  });
  // #endregion
}

void Board::ShowLegalMoves(Piece *piece) {
  // #region ShowLegalMoves
  if (!piece) throw std::runtime_error("Can't show legal moves for piece that does not exist xdd");


  try {
    HideLegalMoves();

  } catch (...) {
    std::cerr << "Error hiting legal moves" << std::endl;
  }

  if (!piece) return;

  for (short i = 0; i < piece->legalMoves.size(); i++) {
    Vector2Int move = piece->legalMoves[i];
    Vector2Int screenPos = ToScreenPosition(move);
    SDL_FRect rect = {screenPos.x + (tileSize / 4), screenPos.y + (tileSize / 4), tileSize / 2,
                      tileSize / 2};
    Renderer renderer({0, 255, 0, 100}, 50);
    Rectangle *moveShower = new Rectangle(rect, renderer);
    GameManager::inGame.AppendElement(moveShower);
    currentLegalMoveShowers.push_back(moveShower);
  }

  // #endregion
}

void Board::HideLegalMoves() {
  // #region HideLegalMoves
  for (short i = 0; i < currentLegalMoveShowers.size(); i++) {
    GameManager::inGame.RemoveElement(currentLegalMoveShowers[i]);
    // delete currentLegalMoveShowers[i];
  }
  currentLegalMoveShowers.clear();
  // #endregion
}

void Board::StartTurn() {
  // #region StartTurn
  std::cout << "Reached here" << std::endl;
  short nOfLegalMoves = 1;

  for (short i = 0; i < boardSize; i++) {
    for (short j = 0; j < boardSize; j++) {
      if (!board[i][j] || board[i][j]->team != currentTurn) continue;

      board[i][j]->legalMoves.clear();
      std::vector<Vector2Int> pseudoLegalMoves = GetLegalMoves(board[i][j]);
      // if (pseudoLegalMoves.size() == 0) continue;

      for (Vector2Int pseudoLegalMove : pseudoLegalMoves) {
        bool isLegal = IsMoveLegal(board[i][j], pseudoLegalMove);
        if (!isLegal) continue;
        if (!board[i][j]) {
          MessageBoxA(nullptr, "Spot should NOT be empty", "Runtime error", MB_OK | MB_ICONERROR);
        }
        board[i][j]->legalMoves.push_back(pseudoLegalMove);
        if (board[i][j]->team == currentTurn) nOfLegalMoves++;
      }
    }
  }
  std::cout << "Reached here 2" << std::endl;

  if (nOfLegalMoves == 0) {

    // exit(0);
    std::cout << "Check-mate" << std::endl;
    GameManager::mainMenu.Present(true);
    GameManager::inGame.Present(false);
    GameManager::inGame.Load();

    for (short i = 0; i < boardSize; i++) {
      for (short j = 0; j < boardSize; j++) {
        if (board[i][j]) {
          delete board[i][j];
          board[i][j] = nullptr;
        }
      }
    }
  }

  // #endregion
}

bool Board::IsMoveLegal(Piece *piece, Vector2Int target) {
  // #region IsMoveLegal

  Piece *originalBoardState[boardSize][boardSize]{nullptr};
  for (short i = 0; i < boardSize; i++) {
    for (short j = 0; j < boardSize; j++) {
      if (board[i][j]) originalBoardState[i][j] = board[i][j];
    }
  }
  Vector2Int originalPiecePosition = piece->position;


  board[target.x][target.y] = piece;
  board[originalPiecePosition.x][originalPiecePosition.y] = nullptr;
  piece->position = target;

  bool isKingInCheck = IsKingInCheck(piece->team);

  for (short i = 0; i < boardSize; i++) {
    for (short j = 0; j < boardSize; j++) {
      board[i][j] = originalBoardState[i][j];
    }
  }

  piece->position = originalPiecePosition;
  return !isKingInCheck;

  // #endregion
}

bool Board::IsKingInCheck(TEAM team) {
  // #region IsKingInCheck
  Piece *king = kings[team];
  if (!king) return false;

  Vector2Int lines[4] = {
      {1, 0},
      {-1, 0},
      {0, 1},
      {0, -1},
  };
  Vector2Int diagonals[4] = {
      {1, 1},
      {-1, 1},
      {1, -1},
      {-1, -1},
  };

  std::optional<Piece *> firstEnemy = std::nullopt;
  for (Vector2Int direction : lines) {
    firstEnemy = std::nullopt;
    GetLineLegalMoves(king->position, direction, king, -1, firstEnemy);

    if (!firstEnemy.has_value()) continue;
    if (firstEnemy.value()->pieceType == PieceType::Rook ||
        firstEnemy.value()->pieceType == PieceType::Queen) {
      return true;
    }

    if (firstEnemy.value()->pieceType == PieceType::King &&
        firstEnemy.value()->team != king->team &&
        Vector2::Distance(king->position, firstEnemy.value()->position) <= 1.5f) {
      return true;
    }
  }

  for (Vector2Int direction : diagonals) {
    firstEnemy = std::nullopt;
    GetDiagonalLegalMoves(king->position, direction, king, -1, firstEnemy);
    if (!firstEnemy.has_value()) continue;
    if (firstEnemy.value()->pieceType == PieceType::Bishop ||
        firstEnemy.value()->pieceType == PieceType::Queen) {
      return true;
    }

    short pawnThreatDirection = currentTurn == 0 ? -1 : 1;
    if (firstEnemy.value()->team != king->team &&
        Vector2::Distance(king->position, firstEnemy.value()->position) <= 1.5f) {

      if (firstEnemy.value()->pieceType == PieceType::King) {
        return true;
      }

      if (firstEnemy.value()->pieceType == PieceType::Pawn &&
          (king->position.y - firstEnemy.value()->position.y) == pawnThreatDirection) {
        return true;
      }
    }
  }

  std::vector<Vector2Int> knightAtackSquares = GetKnightLegalMoves(king);

  for (Vector2Int squares : knightAtackSquares) {
    Piece *atacking = board[squares.x][squares.y];
    if (atacking != nullptr && atacking->pieceType == PieceType::Knight &&
        atacking->team != king->team) {

      return true;
    }
  }


  return false;

  // #endregion
}


bool Board::RequestMove(Piece *piece, Vector2Int target) {
  // #region RequestMove



  if (piece->legalMoves.size() == 0) return false;
  if (piece->team != currentTurn) return false;

  auto it = std::find(piece->legalMoves.begin(), piece->legalMoves.end(), target);
  if (it == piece->legalMoves.end()) return false;

  Piece *capturedPiece = board[target.x][target.y];
  board[target.x][target.y] = piece;
  board[piece->position.x][piece->position.y] = nullptr;
  piece->position = target;


  if (capturedPiece) {
    if (capturedPiece->pieceType == PieceType::King) {
      kings[capturedPiece->team] = nullptr;
    }
    if (lastMovedPiece == capturedPiece) {
      lastMovedPiece = nullptr;
    }
    delete capturedPiece;
    capturedPiece = nullptr;
  }

  try {
    HideLegalMoves();
    currentTurn = currentTurn == 0 ? 1 : 0;
    StartTurn();

  } catch (...) {
    std::cerr << "Error hiting legal moves" << std::endl;
  }
  return true;
  // #endregion
}


std::vector<Vector2Int> Board::GetLegalMoves(Piece *piece) {
  // #region GetLegalMoves
  std::vector<Vector2Int> moves;

  switch (piece->pieceType) {
  case PieceType::Pawn:
    return GetPawnLegalMoves(piece);
  case PieceType::Knight:
    return GetKnightLegalMoves(piece);
  case PieceType::Bishop:
    return GetBishopLegalMoves(piece);
  case PieceType::Rook:
    return GetRookLegalMoves(piece);
  case PieceType::Queen:
    return GetQueenLegalMoves(piece);
  case PieceType::King:
    return GetKingLegalMoves(piece);

  default:
    throw std::runtime_error("Unknown piece type: " + std::to_string(piece->pieceType));
  }
  // #endregion
}

std::vector<Vector2Int> Board::GetPawnLegalMoves(Piece *piece) {
  // #region GetPawnLegalMoves
  std::vector<Vector2Int> moves;
  Vector2 direction = (piece->team == 0) ? Vector2(0, 1) : Vector2(0, -1);
  Vector2 startTile =
      (piece->team == 0) ? Vector2(piece->position.x, 1) : Vector2(piece->position.x, 6);

  short limit = piece->position.y == startTile.y ? 2 : 1;

  std::vector<Vector2Int> lineMoves = GetLineLegalMoves(piece->position, direction, piece, limit);
  for (Vector2Int move : lineMoves) {
    if (board[move.x][move.y] == nullptr) {
      moves.push_back(move);
    }
  }


  Vector2Int captures[2]{
      Vector2Int(1, direction.y),
      Vector2Int(-1, direction.y),
  };

  for (Vector2Int direction : captures) {
    std::vector<Vector2Int> captureMoves =
        GetDiagonalLegalMoves(piece->position, direction, piece, 1);

    for (Vector2Int move : captureMoves) {
      if (board[move.x][move.y] != nullptr && board[move.x][move.y]->team != piece->team) {
        moves.push_back(move);
      }
    }
  }
  // TODO: Implament en passant

  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetRookLegalMoves(Piece *piece) {
  // #region GetRookLegalMoves
  std::vector<Vector2Int> moves;
  Vector2Int directions[4] = {
      {1, 0},
      {-1, 0},
      {0, 1},
      {0, -1},
  };


  for (Vector2Int direction : directions) {
    std::vector<Vector2Int> lineMoves = GetLineLegalMoves(piece->position, direction, piece);
    moves.insert(moves.end(), lineMoves.begin(), lineMoves.end());
  }

  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetBishopLegalMoves(Piece *piece) {
  // #region GetBishopLegalMoves
  std::vector<Vector2Int> moves;

  Vector2Int directions[4] = {
      {1, 1},
      {-1, 1},
      {1, -1},
      {-1, -1},
  };

  for (Vector2Int direction : directions) {
    std::vector<Vector2Int> lineMoves = GetDiagonalLegalMoves(piece->position, direction, piece);
    moves.insert(moves.end(), lineMoves.begin(), lineMoves.end());
  }

  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetKnightLegalMoves(Piece *piece) {
  // #region GetKnightLegalMoves
  std::vector<Vector2Int> moves;

  Vector2Int offsets[8]{
      {-1, -2}, {1, -2}, {-1, 2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1},

  };

  for (Vector2Int offset : offsets) {
    Vector2Int move = piece->position + offset;
    if (move.x < 0 || move.x >= boardSize || move.y < 0 || move.y >= boardSize) continue;
    if (board[move.x][move.y] != nullptr && board[move.x][move.y]->team == piece->team) continue;
    moves.push_back(move);
  }


  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetQueenLegalMoves(Piece *piece) {
  // #region GetQueenLegalMoves
  std::vector<Vector2Int> moves;
  Vector2Int lines[4] = {
      {1, 0},
      {-1, 0},
      {0, 1},
      {0, -1},
  };
  Vector2Int diagonals[4] = {
      {1, 1},
      {-1, 1},
      {1, -1},
      {-1, -1},
  };
  for (Vector2Int direction : lines) {
    std::vector<Vector2Int> lineMoves = GetLineLegalMoves(piece->position, direction, piece);
    moves.insert(moves.end(), lineMoves.begin(), lineMoves.end());
  }

  for (Vector2Int direction : diagonals) {
    std::vector<Vector2Int> lineMoves = GetDiagonalLegalMoves(piece->position, direction, piece);
    moves.insert(moves.end(), lineMoves.begin(), lineMoves.end());
  }

  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetKingLegalMoves(Piece *piece) {
  // #region GetQueenLegalMoves
  std::vector<Vector2Int> moves;
  Vector2Int lines[4] = {
      {1, 0},
      {-1, 0},
      {0, 1},
      {0, -1},
  };
  Vector2Int diagonals[4] = {
      {1, 1},
      {-1, 1},
      {1, -1},
      {-1, -1},
  };

  for (Vector2Int direction : lines) {
    std::vector<Vector2Int> lineMoves = GetLineLegalMoves(piece->position, direction, piece, 1);
    moves.insert(moves.end(), lineMoves.begin(), lineMoves.end());
  }

  for (Vector2Int direction : diagonals) {
    std::vector<Vector2Int> lineMoves = GetDiagonalLegalMoves(piece->position, direction, piece, 1);
    moves.insert(moves.end(), lineMoves.begin(), lineMoves.end());
  }

  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetLineLegalMoves(Vector2 startPosition, Vector2 direction,
                                                 Piece *piece, short limit) {
  // #region GetLineLegalMoves
  std::optional<Piece *> _;
  return GetLineLegalMoves(startPosition, direction, piece, limit, _);
  // #endregion
}
std::vector<Vector2Int> Board::GetLineLegalMoves(Vector2 startPosition, Vector2 direction,
                                                 Piece *piece, std::optional<Piece *> &firstEnemy) {
  // #region GetLineLegalMoves
  return GetLineLegalMoves(startPosition, direction, piece, -1, firstEnemy);
  // #endregion
}

std::vector<Vector2Int> Board::GetLineLegalMoves(Vector2 startPosition, Vector2 direction,
                                                 Piece *piece, short limit,
                                                 std::optional<Piece *> &firstEnemy) {
  // #region GetLineLegalMoves
  std::vector<Vector2Int> moves;

  short realLimit;

  if (direction.x != 0) {
    realLimit = (direction.x == 1) ? (boardSize - piece->position.x) - 1 : piece->position.x;
  } else {
    realLimit = (direction.y == 1) ? (boardSize - piece->position.y) - 1 : piece->position.y;
  }
  if (limit != -1) realLimit = std::min(realLimit, limit);

  for (short positions = 1; positions <= realLimit; positions++) {
    Vector2Int move = piece->position + (direction * positions);
    move.x = std::clamp(move.x, 0, boardSize - 1);
    move.y = std::clamp(move.y, 0, boardSize - 1);
    if (!CheckMove(move, moves)) {
      if (board[move.x][move.y] != nullptr && board[move.x][move.y]->team != piece->team) {
        moves.push_back(move);
        firstEnemy = board[move.x][move.y];
      }
      break;
    }
  }


  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetDiagonalLegalMoves(Vector2 startPosition, Vector2 direction,
                                                     Piece *piece, short limit) {
  // #region GetDiagonalLegalMoves
  std::optional<Piece *> _;
  return GetDiagonalLegalMoves(startPosition, direction, piece, limit, _);
  // #endregion
}


std::vector<Vector2Int> Board::GetDiagonalLegalMoves(Vector2 startPosition, Vector2 direction,
                                                     Piece *piece,
                                                     std::optional<Piece *> &firstEnemy) {
  // #region GetDiagonalLegalMoves
  return GetDiagonalLegalMoves(startPosition, direction, piece, -1, firstEnemy);
  // #endregion
}

std::vector<Vector2Int> Board::GetDiagonalLegalMoves(Vector2 startPosition, Vector2 direction,
                                                     Piece *piece, short limit,
                                                     std::optional<Piece *> &firstEnemy) {
  // #region GetDiagonalLegalMoves
  std::vector<Vector2Int> moves;

  short limitX = direction.x == 1 ? (boardSize - piece->position.x) - 1 : piece->position.x;
  short limitY = direction.y == 1 ? (boardSize - piece->position.y) - 1 : piece->position.y;

  short realLimit = std::min(limitX, limitY);
  if (limit != -1) realLimit = std::min(realLimit, limit);


  for (short positions = 1; positions <= realLimit; positions++) {
    Vector2Int move = piece->position + (direction * positions);
    move.x = std::clamp(move.x, 0, boardSize - 1);
    move.y = std::clamp(move.y, 0, boardSize - 1);

    if (!CheckMove(move, moves)) {
      if (board[move.x][move.y] != nullptr && board[move.x][move.y]->team != piece->team) {
        moves.push_back(move);
        firstEnemy = board[move.x][move.y];
      }
      break;
    }
  }


  return moves;
  // #endregion
}


bool Board::CheckMove(Vector2Int move, std::vector<Vector2Int> &moves) {
  // #region CheckMove
  if (board[move.x][move.y]) return false;
  moves.push_back(move);
  return true;
  // return true;
  // #endregion
}


} // namespace Chess::Game
