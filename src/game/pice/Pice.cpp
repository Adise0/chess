#include "../../gameManager/GameManager.h"
#include "../../ui/renderer/Renderer.h"
#include "../../windowManager/WindowManager.h"
#include "../board/Board.h"
#include "Piece.h"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <string>


namespace Chess::Game {
using namespace Rendering;

Piece::Piece(POSITION startPosition, PieceType pieceType, TEAM team)
    : position(startPosition), pieceType(pieceType), team(team) {

  // POSITION screenPosition = board.ToScreenPosition(startPosition);
  // SDL_FRect rect = {screenPosition.x, screenPosition.y, WindowManager::pieceX, WindowManager::pieceY};
  SDL_FRect rect = {0, 0, Board::pieceSize, Board::pieceSize};
  SDL_Texture *pieceTexture = WindowManager::LoadSprite(GetPieceSprite());
  Renderer pieceRenderer(pieceTexture, NULL, NULL, 1);
  element = new Button(rect, pieceRenderer);
  GameManager::inGame.AppendElement(element);
}


const char *Piece::GetPieceSprite() {

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

  return ("assets/sprites/pieces/" + teamStr + name + ".png").c_str();
}

} // namespace Chess::Game

// namespace Chess::Game
