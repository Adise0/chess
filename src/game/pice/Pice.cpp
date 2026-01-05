#include "Pice.h"
#include "../../gameManager/GameManager.h"
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
  SDL_FRect rect = {0, 0, 70, 70};
  SDL_Texture *piceTexture = WindowManager::LoadSprite(GetPiceSprite());
  Renderer piceRenderer(piceTexture, NULL, NULL, 1);
  element = new Button(rect, piceRenderer);
  GameManager::inGame.AppendElement(element);
}


const char *Pice::GetPiceSprite() {

  std::string teamStr = team == 0 ? "black" : "white";
  std::string name;
  switch (piceType) {
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
    throw std::runtime_error("Unknown pice type: " + std::to_string(piceType));
  }

  return ("assets/sprites/pices/" + teamStr + name + ".png").c_str();
}

} // namespace Chess::Game

// namespace Chess::Game
