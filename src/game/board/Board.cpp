#include "Board.h"
#include "../../gameManager/GameManager.h"
#include "../../windowManager/WindowManager.h"
#include <algorithm>
#include <iostream>
#include <string>


namespace Chess::Game {

#define BOARD_PADDING 20


Board::Board() {
  // #region Board
  ConstructBoard();
  currentTurn = 1;
  selectedPiece = nullptr;
  currentLegalMoves.clear();
  currentLegalMoveShowers.clear();
  // #endregion
}

void Board::ConstructBoard() {
  // #region ConstructBoard

  int initialX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  int initialY = BOARD_PADDING;
  int currentX = initialX;
  int currentY = initialY;

  Renderer lightTileRenderer({240, 217, 181, 255}, -1);
  Renderer darkTileRenderer({181, 136, 99, 255}, -1);


  for (size_t col = 0; col < boardSize; col++) {
    currentY = initialY;
    for (size_t row = 0; row < boardSize; row++) {
      SDL_FRect tileRect = {currentX, currentY, tileSize, tileSize};

      Renderer *renderer;
      if (row % 2 == 0) {
        if (col % 2 == 0) renderer = &lightTileRenderer;
        else renderer = &darkTileRenderer;
      } else {
        if (col % 2 == 0) renderer = &darkTileRenderer;
        else renderer = &lightTileRenderer;
      }

      CreateTile(tileRect, *renderer);
      ConfigurePiece({
          (short)row,
          (short)col,
      });
      currentY += tileSize;
    }
    currentX += tileSize;
  }



  // #endregion
}

void Board::CreateTile(SDL_FRect rect, Renderer renderer) {
  // #region CreateTile
  Rectangle *createdTile = new Rectangle(rect, renderer);
  GameManager::inGame.AppendElement(createdTile);
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
  float offsetY = BOARD_PADDING;


  return {boardPosition.x * tileSize + offsetX, boardPosition.y * tileSize + offsetY};
  // #endregion
}

Vector2Int Board::GetClosestTile(Vector2 screenPosition) {
  // #region GetClosestTile
  float offsetX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  float offsetY = BOARD_PADDING;

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

bool Board::EnsureLegal(Vector2Int targetTile, Vector2Int originalTile, Piece *piece) {

  board[targetTile.x][targetTile.y] = piece;
  board[piece->position.x][piece->position.y] = nullptr;
  piece->position = targetTile;

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
  Piece *king = currentTurn == 0 ? team0King : team1King;
  bool cancelMove = false;
  for (Vector2Int direction : lines) {
    firstEnemy = std::nullopt;
    GetLineLegalMoves(king->position, direction, king, -1, firstEnemy);

    if (!firstEnemy.has_value()) continue;
    if (firstEnemy.value()->pieceType == PieceType::Rook ||
        firstEnemy.value()->pieceType == PieceType::Queen) {
      cancelMove = true;
      break;
    }

    if (firstEnemy.value()->pieceType == PieceType::King &&
        firstEnemy.value()->team != king->team &&
        Vector2::Distance(king->position, firstEnemy.value()->position) <= 1.5f) {
      cancelMove = true;
      break;
    }
  }

  if (!cancelMove) {
    for (Vector2Int direction : diagonals) {
      firstEnemy = std::nullopt;
      GetDiagonalLegalMoves(king->position, direction, king, -1, firstEnemy);
      if (!firstEnemy.has_value()) continue;
      if (firstEnemy.value()->pieceType == PieceType::Bishop ||
          firstEnemy.value()->pieceType == PieceType::Queen) {

        cancelMove = true;
        break;
      }

      short bigNono = currentTurn == 0 ? -1 : 1;
      if (firstEnemy.value()->team != king->team &&
          Vector2::Distance(king->position, firstEnemy.value()->position) <= 1.5f) {

        if (firstEnemy.value()->pieceType == PieceType::King) {
          cancelMove = true;
          break;
        }

        if (firstEnemy.value()->pieceType == PieceType::Pawn &&
            (king->position.y - firstEnemy.value()->position.y) == bigNono) {
          cancelMove = true;
          break;
        } else {
          continue;
        }
      }
    }
  }

  if (!cancelMove) {
    Piece *king = currentTurn == 0 ? team0King : team1King;
    std::vector<Vector2Int> knightAtackSquares = GetKnightLegalMoves(king);

    for (Vector2Int squares : knightAtackSquares) {
      Piece *atacking = board[squares.x][squares.y];
      if (atacking != nullptr && atacking->pieceType == PieceType::Knight &&
          atacking->team != king->team) {
        cancelMove = true;
        break;
      }
    }
  }


  return cancelMove;
};

void Board::ConfigurePiece(Vector2Int boardPosition) {
  // #region ConfigurePiece
  Piece *piece = board[boardPosition.x][boardPosition.y];
  if (!piece) return;
  Vector2Int screenPosition = ToScreenPosition(boardPosition);

  if (piece->pieceType == PieceType::King) {
    if (piece->team == 0) team0King = piece;
    else team1King = piece;
  }

  piece->element->OnClick([this, piece] { this->CalculateLegalMoves(piece); });
  piece->element->OnDragStart([this, piece] { this->CalculateLegalMoves(piece); });

  piece->element->OnDragEnd([this, piece](Vector2 dropPosition) {
    Vector2Int targetTile = Board::GetClosestTile(dropPosition);
    Vector2Int originalTile = piece->position;
    Vector2Int originalSceenPos = Board::ToScreenPosition(piece->position);
    Vector2Int newScreenPos = Board::ToScreenPosition(targetTile);

    if (selectedPiece != piece) {
      std::cout << "Piece missmatch\n";
      piece->element->SetPosition(originalSceenPos.x, originalSceenPos.y);
      return;
    }


    auto found = std::find_if(
        currentLegalMoves.begin(), currentLegalMoves.end(),
        [targetTile](Vector2Int pos) { return pos.x == targetTile.x && pos.y == targetTile.y; });
    if (found == currentLegalMoves.end()) {
      piece->element->SetPosition(originalSceenPos.x, originalSceenPos.y);
      return;
    }

    Piece *target = board[targetTile.x][targetTile.y];
    bool cancelMove = EnsureLegal(targetTile, originalTile, piece);


    if (cancelMove) {
      board[originalTile.x][originalTile.y] = piece;
      board[piece->position.x][piece->position.y] = nullptr;
      piece->position = originalTile;
      piece->element->SetPosition(originalSceenPos.x, originalSceenPos.y);

      return;
    } else {
      if (target) delete target;
      piece->element->SetPosition(newScreenPos.x, newScreenPos.y);

      Vector2 offsets[8]{
          {-1, -1}, {1, -1}, {-1, 1}, {1, -1}, {0, -1}, {0, 1}, {-1, 0}, {1, 0},
      };


      bool anyLegal = false;
      for (Vector2 offset : offsets) {
        for (size_t i = 0; i < 2; i++) {
          Piece *king = currentTurn == 0 ? team0King : team1King;
          if (!EnsureLegal(king->position, king->position + offset, king)) {
            anyLegal = true;
          }
        }
      }
      if (!anyLegal) {
        GameManager::inGame.Present(false);
        GameManager::mainMenu.Present(true);
      }
    }

    // TEMP
    for (size_t i = 0; i < currentLegalMoveShowers.size(); i++) {
      GameManager::inGame.RemoveElement(currentLegalMoveShowers[i]);
      delete currentLegalMoveShowers[i];
    }
    currentLegalMoveShowers.clear();

    currentTurn = (currentTurn == 0) ? 1 : 0;
  });



  piece->element->SetPosition(screenPosition.x, screenPosition.y);
  // #endregion
}

void Board::CalculateLegalMoves(Piece *piece) {
  // #region CalculateLegalMoves

  selectedPiece = piece;
  if (piece->team != currentTurn) {
    currentLegalMoves.clear();
    return;
  }
  currentLegalMoves = GetLegalMoves(piece);



  // TEMP
  for (size_t i = 0; i < currentLegalMoveShowers.size(); i++) {
    GameManager::inGame.RemoveElement(currentLegalMoveShowers[i]);
    delete currentLegalMoveShowers[i];
  }
  currentLegalMoveShowers.clear();
  for (size_t i = 0; i < currentLegalMoves.size(); i++) {
    Vector2Int move = currentLegalMoves[i];
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
  // #endregion
}


} // namespace Chess::Game
