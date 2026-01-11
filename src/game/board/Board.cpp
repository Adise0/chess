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
  return currrentTurn;
  // #endregion
}

POSITION Board::ToScreenPosition(POSITION boardPosition) {
  // #region ToScreenPosition
  float offsetX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  float offsetY = BOARD_PADDING;


  return {(short)(boardPosition.x * tileSize + offsetX),
          (short)(boardPosition.y * tileSize + offsetY)};
  // #endregion
}

POSITION Board::GetClosestTile(float x, float y) {
  // #region GetClosestTile
  float offsetX = (WindowManager::resolutionX / 2) - (boardSize / 2 * tileSize);
  float offsetY = BOARD_PADDING;

  float offsetedX = x - offsetX;
  float offsetedY = y - offsetY;

  float boardX = (offsetedX / tileSize);
  float boardY = (offsetedY / tileSize);

  int row = (int)std::lround(boardX);
  int col = (int)std::lround(boardY);

  row = std::clamp(row, 0, boardSize - 1);
  col = std::clamp(col, 0, boardSize - 1);


  return {(short)row, (short)col};
  // #endregion
};

void Board::ConfigurePiece(POSITION boardPosition) {
  // #region ConfigurePiece
  Piece *piece = board[boardPosition.x][boardPosition.y];
  if (!piece) return;
  POSITION screenPosition = ToScreenPosition(boardPosition);

  piece->element->OnClick([this, piece] { this->CalculateLegalMoves(piece); });
  piece->element->OnDragStart([this, piece] { this->CalculateLegalMoves(piece); });

  piece->element->OnDragEnd([this, piece](float x, float y) {
    POSITION tile = Board::GetClosestTile(x, y);
    POSITION originalSceenPos = Board::ToScreenPosition(piece->position);
    POSITION newScreenPos = Board::ToScreenPosition(tile);

    if (selectedPiece != piece) return;


    auto found = std::find_if(currentLegalMoves.begin(), currentLegalMoves.end(),
                              [tile](POSITION pos) { return pos.x == tile.x && pos.y == tile.y; });
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
  });



  piece->element->SetPosition(screenPosition.x, screenPosition.y);
  // #endregion
}

void Board::CalculateLegalMoves(Piece *piece) {
  // #region CalculateLegalMoves
  std::vector<POSITION> legalMoves = GetLegalMoves(piece);
  currentLegalMoves = legalMoves;
  selectedPiece = piece;

  // TEMP
  for (size_t i = 0; i < currentLegalMoveShowers.size(); i++) {
    GameManager::inGame.RemoveElement(currentLegalMoveShowers[i]);
    delete currentLegalMoveShowers[i];
  }
  currentLegalMoveShowers.clear();
  for (size_t i = 0; i < currentLegalMoves.size(); i++) {
    POSITION move = currentLegalMoves[i];
    POSITION screenPos = ToScreenPosition(move);
    SDL_FRect rect = {screenPos.x + (tileSize / 4), screenPos.y + (tileSize / 4), tileSize / 2,
                      tileSize / 2};
    Renderer renderer({0, 255, 0, 100}, 50);
    Rectangle *moveShower = new Rectangle(rect, renderer);
    GameManager::inGame.AppendElement(moveShower);
    currentLegalMoveShowers.push_back(moveShower);
  }


  // #endregion
}

std::vector<POSITION> Board::GetLegalMoves(Piece *piece) {
  // #region GetLegalMoves
  std::vector<POSITION> moves;

  switch (piece->pieceType) {
  case PieceType::Pawn:
    return GetPawnLegalMoves(piece);
    break;
  case PieceType::Rook:
    return GetRookLegalMoves(piece);
    break;

  default:
    throw std::runtime_error("Unknown piece type: " + std::to_string(piece->pieceType));
  }
  // #endregion
}

std::vector<POSITION> Board::GetPawnLegalMoves(Piece *piece) {
  // #region GetPawnLegalMoves
  std::vector<POSITION> moves;

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

  // TODO: Implement en-passant when turns are implemented
  // TODO: Implament captures

  return moves;
  // #endregion
}

std::vector<POSITION> Board::GetRookLegalMoves(Piece *piece) {
  // #region GetRookLegalMoves
  std::vector<POSITION> moves;



  for (short y = piece->position.y - 1; y >= 0; y--) {
    POSITION pos = {piece->position.x, y};
    if (board[pos.x][pos.y]) break;
    moves.push_back(pos);
  }
  for (short y = piece->position.y + 1; y < boardSize; y++) {
    POSITION pos = {piece->position.x, y};
    if (board[pos.x][pos.y]) break;
    moves.push_back(pos);
  }

  for (short x = piece->position.x - 1; x >= 0; x--) {
    POSITION pos = {x, piece->position.y};
    if (board[pos.x][pos.y]) break;
    moves.push_back(pos);
  }
  for (short x = piece->position.x + 1; x < boardSize; x++) {
    POSITION pos = {x, piece->position.y};
    if (board[pos.x][pos.y]) break;
    moves.push_back(pos);
  }


  // TODO: Implament captures
  return moves;
  // #endregion
}

} // namespace Chess::Game
