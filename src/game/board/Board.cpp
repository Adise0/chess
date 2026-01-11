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

void Board::ConfigurePiece(Vector2Int boardPosition) {
  // #region ConfigurePiece
  Piece *piece = board[boardPosition.x][boardPosition.y];
  if (!piece) return;
  Vector2Int screenPosition = ToScreenPosition(boardPosition);

  piece->element->OnClick([this, piece] { this->CalculateLegalMoves(piece); });
  piece->element->OnDragStart([this, piece] { this->CalculateLegalMoves(piece); });

  piece->element->OnDragEnd([this, piece](Vector2 dropPosition) {
    Vector2Int tile = Board::GetClosestTile(dropPosition);
    Vector2Int originalSceenPos = Board::ToScreenPosition(piece->position);
    Vector2Int newScreenPos = Board::ToScreenPosition(tile);

    if (selectedPiece != piece) {
      std::cout << "Piece missmatch\n";
      piece->element->SetPosition(originalSceenPos.x, originalSceenPos.y);
      return;
    }


    auto found =
        std::find_if(currentLegalMoves.begin(), currentLegalMoves.end(),
                     [tile](Vector2Int pos) { return pos.x == tile.x && pos.y == tile.y; });
    if (found == currentLegalMoves.end()) {
      piece->element->SetPosition(originalSceenPos.x, originalSceenPos.y);
      std::cout << "Illegal move to (" << tile.x << ", " << tile.y << ")\n";
      return;
    }

    piece->element->SetPosition(newScreenPos.x, newScreenPos.y);
    board[tile.x][tile.y] = piece;
    board[piece->position.x][piece->position.y] = nullptr;
    piece->position = tile;
    std::cout << "Legal move to (" << tile.x << ", " << tile.y << ")\n";

    // TEMP
    for (size_t i = 0; i < currentLegalMoveShowers.size(); i++) {
      GameManager::inGame.RemoveElement(currentLegalMoveShowers[i]);
      delete currentLegalMoveShowers[i];
    }
    currentLegalMoveShowers.clear();

    currentTurn = (currentTurn == 0) ? 1 : 0;
    // Advance turn
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

  default:
    throw std::runtime_error("Unknown piece type: " + std::to_string(piece->pieceType));
  }
  // #endregion
}

std::vector<Vector2Int> Board::GetPawnLegalMoves(Piece *piece) {
  // #region GetPawnLegalMoves
  std::vector<Vector2Int> moves;

  short advanceTile = (piece->team == 0) ? 1 : -1;
  short startRow = (piece->team == 0) ? 1 : 6;


  if (piece->team == 0) {
    if (piece->position.y + 1 >= boardSize) return moves;
  } else {
    if (piece->position.y - 1 < 0) return moves;
  }

  if (piece->position.y == startRow && !board[piece->position.x][startRow + advanceTile] &&
      !board[piece->position.x][startRow + advanceTile * 2])
    moves.push_back({piece->position.x, (short)(startRow + advanceTile * 2)});

  if (!board[piece->position.x][piece->position.y + advanceTile])
    moves.push_back({piece->position.x, (short)(piece->position.y + advanceTile)});

  if (piece->team == 1 && board[piece->position.x - 1][piece->position.y - 1] &&
      board[piece->position.x - 1][piece->position.y - 1]->team == 0) // White pawn left kill
    moves.push_back(
        {(short)(piece->position.x - 1), (short)(piece->position.y - 1 + advanceTile + 1)});

  // piece->team == 0 && board[piece->position.x - 1][piece->position.y - 1]

  // TODO: Implement en-passant when turns are implemented
  // TODO: Implament captures

  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetRookLegalMoves(Piece *piece) {
  // #region GetRookLegalMoves
  std::vector<Vector2Int> moves;
  for (short y = piece->position.y - 1; y >= 0; y--)
    if (!CheckMove({piece->position.x, y}, moves)) break;
  for (short y = piece->position.y + 1; y < boardSize; y++)
    if (!CheckMove({piece->position.x, y}, moves)) break;
  for (short x = piece->position.x - 1; x >= 0; x--)
    if (!CheckMove({x, piece->position.y}, moves)) break;
  for (short x = piece->position.x + 1; x < boardSize; x++)
    if (!CheckMove({x, piece->position.y}, moves)) break;
  // TODO: Implament captures
  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetKnightLegalMoves(Piece *piece) {
  // #region GetKnightLegalMoves
  std::vector<Vector2Int> moves;

  short x = piece->position.x + 1;
  short y = piece->position.y - 2;

  if (!board[x][y]) moves.push_back({x, y});

  x -= 2;
  if (!board[x][y]) moves.push_back({x, y});

  y += 4;
  if (!board[x][y]) moves.push_back({x, y});

  x += 2;
  if (!board[x][y]) moves.push_back({x, y});

  x += 1;
  y -= 1;
  if (!board[x][y]) moves.push_back({x, y});

  x -= 4;
  if (!board[x][y]) moves.push_back({x, y});

  y -= 2;
  if (!board[x][y]) moves.push_back({x, y});

  x += 4;
  if (!board[x][y]) moves.push_back({x, y});

  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetQueenLegalMoves(Piece *piece) {
  // #region GetQueenLegalMoves
  std::vector<Vector2Int> moves;

  for (short y = piece->position.y - 1; y >= 0; y--) {
    Vector2Int move = {piece->position.x, y};
    if (!CheckMove(move, moves)) {
      if (board[move.x][move.y] != nullptr && board[move.x][move.y]->team != piece->team) {
        moves.push_back(move);
      }
      break;
    }
  }


  for (short y = piece->position.y + 1; y < boardSize; y++) {
    Vector2Int move = {piece->position.x, y};
    if (!CheckMove(move, moves)) {
      if (board[move.x][move.y] != nullptr && board[move.x][move.y]->team != piece->team) {
        moves.push_back(move);
      }
      break;
    }
  }

  for (short x = piece->position.x - 1; x >= 0; x--) {
    Vector2Int move = {x, piece->position.y};
    if (!CheckMove(move, moves)) {
      if (board[move.x][move.y] != nullptr && board[move.x][move.y]->team != piece->team) {
        moves.push_back(move);
      }
      break;
    }
  }
  for (short x = piece->position.x + 1; x < boardSize; x++) {
    Vector2Int move = {x, piece->position.y};
    if (!CheckMove(move, moves)) {
      if (board[move.x][move.y] != nullptr && board[move.x][move.y]->team != piece->team) {
        moves.push_back(move);
      }
      break;
    }
  }



  for (short offset = 1; offset < (boardSize - piece->position.x); offset++) {
    Vector2Int move = {(short)(piece->position.x + offset), (short)(piece->position.y - offset)};
    if (!CheckMove(move, moves)) break;
  }
  for (short offset = 1; offset < (boardSize - piece->position.x); offset++) {
    Vector2Int move = {(short)(piece->position.x + offset), (short)(piece->position.y + offset)};
    if (!CheckMove(move, moves)) break;
  }

  for (short offset = -1; piece->position.x + offset >= 0; offset--) {
    Vector2Int move = {(short)(piece->position.x + offset), (short)(piece->position.y - offset)};
    if (!CheckMove(move, moves)) break;
  }
  for (short offset = -1; piece->position.x + offset >= 0; offset--) {
    Vector2Int move = {(short)(piece->position.x + offset), (short)(piece->position.y + offset)};
    if (!CheckMove(move, moves)) break;
  }

  // TODO: Implament captures
  return moves;
  // #endregion
}

std::vector<Vector2Int> Board::GetBishopLegalMoves(Piece *piece) {
  std::vector<Vector2Int> moves;


  for (short offset = 1; offset < (boardSize - piece->position.x); offset++) {
    Vector2Int move = {(short)(piece->position.x + offset), (short)(piece->position.y - offset)};
    if (!CheckMove(move, moves)) break;
  }
  for (short offset = 1; offset < (boardSize - piece->position.x); offset++) {
    Vector2Int move = {(short)(piece->position.x + offset), (short)(piece->position.y + offset)};
    if (!CheckMove(move, moves)) break;
  }

  for (short offset = -1; piece->position.x + offset >= 0; offset--) {
    Vector2Int move = {(short)(piece->position.x + offset), (short)(piece->position.y - offset)};
    if (!CheckMove(move, moves)) break;
  }
  for (short offset = -1; piece->position.x + offset >= 0; offset--) {
    Vector2Int move = {(short)(piece->position.x + offset), (short)(piece->position.y + offset)};
    if (!CheckMove(move, moves)) break;
  }

  return moves;
}

bool Board::CheckMove(Vector2Int move, std::vector<Vector2Int> &moves) {
  // #region CheckMove
  if (board[move.x][move.y]) return false;
  moves.push_back(move);
  return true;
  // #endregion
}


} // namespace Chess::Game
