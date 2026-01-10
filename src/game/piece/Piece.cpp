#include "Piece.h"
#include "../../gameManager/GameManager.h"
#include "../../ui/renderer/Renderer.h"
#include "../../windowManager/WindowManager.h"
#include "../board/Board.h"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <string>


namespace Chess::Game {
using namespace Rendering;

Piece::Piece(POSITION startPosition, PieceType pieceType, TEAM team)
    : position(startPosition), pieceType(pieceType), team(team) {
  // #region Pice
  CreateElement();

  element->OnDragEnd([this](float x, float y) {
    POSITION tile = Board::GetClosestTile(x, y);
    POSITION screenPos = Board::ToScreenPosition(tile);
    this->element->SetPosition(screenPos.x, screenPos.y);
  });

  // #endregion
}


void Piece::CreateElement() {
  // #region CreateElement
  SDL_FRect rendererRect = {(Board::tileSize - Board::pieceSize) / 2,
                            (Board::tileSize - Board::pieceSize) / 2, Board::pieceSize,
                            Board::pieceSize};

  SDL_FRect rect = {0, 0, Board::tileSize, Board::tileSize};
  SDL_Texture *pieceTexture = WindowManager::LoadSprite(GetPieceSprite());
  Renderer pieceRenderer(pieceTexture, NULL, pieceTexture, 1);
  element = new Draggable(rect, rendererRect, pieceRenderer);
  GameManager::inGame.AppendElement(element);

  // #endregion
}


std::string Piece::GetPieceSprite() {
  // #region GetPieceSprite
  std::string teamStr = team == 0 ? "black" : "white";
  std::string name;
  switch (pieceType) {
  case PieceType::Pawn:
    name = "Pawn";
    break;
  case PieceType::Rook:
    name = "Rook";
    break;
  case PieceType::Knight:
    name = "Knight";
    break;
  case PieceType::Bishop:
    name = "Bishop";
    break;
  case PieceType::Queen:
    name = "Queen";
    break;
  case PieceType::King:
    name = "King";
    break;
  default:
    throw std::runtime_error("Unknown piece type: " + std::to_string(pieceType));
  }

  return ("assets/sprites/pieces/" + teamStr + name + ".png");
  // #endregion
}
} // namespace Chess::Game
