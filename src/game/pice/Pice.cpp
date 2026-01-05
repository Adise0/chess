#include "Pice.h"
#include "../../ui/renderer/Renderer.h"
#include "../../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <string>


namespace Chess::Game {
using namespace Rendering;

Pice::Pice(POSITION startPosition, PieceType piceType, TEAM team)
    : position(startPosition), piceType(piceType), team(team) {

  // POSITION screenPosition = board.ToScreenPosition(startPosition);
  // SDL_FRect rect = {screenPosition.x, screenPosition.y, WindowManager::piceX, WindowManager::piceY};
  SDL_FRect rect = {0, 0, WindowManager::piceX, WindowManager::piceY};
  SDL_Texture *piceTexture = WindowManager::LoadSprite(GetPiceSprite());
  Renderer piceRenderer(piceTexture);
  element = new Button(rect, piceRenderer);
}


const char *Pice::GetPiceSprite() {
  switch (piceType) {
  case PieceType::wPawn:
    return "assets/pices/whitePawn.png";
    break;
  case PieceType::wRook:
    return "assets/pices/whiteRook.png";
    break;
  case PieceType::wKnight:
    return "assets/pices/whiteKnight.png";
    break;
  case PieceType::wBishop:
    return "assets/pices/whiteBishop.png";
    break;
  case PieceType::wQueen:
    return "assets/pices/whiteQueen.png";
    break;
  case PieceType::wKing:
    return "assets/pices/whiteKing.png";
    break;
  // Blackerrrs
  case PieceType::bPawn:
    return "assets/pices/blackPawn.png";
    break;
  case PieceType::bRook:
    return "assets/pices/blackRook.png";
    break;
  case PieceType::bKnight:
    return "assets/pices/blackKnight.png";
    break;
  case PieceType::bBishop:
    return "assets/pices/blackBishop.png";
    break;
  case PieceType::bQueen:
    return "assets/pices/blackQueen.png";
    break;
  case PieceType::bKing:
    return "assets/pices/blackKing.png";
    break;

  default:
    throw std::runtime_error("Unknown pice type: " + std::to_string(piceType));
  }
}

} // namespace Chess::Game

// namespace Chess::Game
