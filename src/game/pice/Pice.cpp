#include "Pice.h"
#include "../../ui/renderer/Renderer.h"
#include "../../windowManager/WindowManager.h"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <string>


namespace Chess::Game {
using namespace Rendering;

Pice::Pice(POSITION startPosition, PiceType piceType, TEAM team)
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
  case PiceType::Pawn:
    return "assets/pices/pawn.png";

  default:
    throw std::runtime_error("Unknown pice type: " + std::to_string(piceType));
  }
}
} // namespace Chess::Game
