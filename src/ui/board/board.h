#pragma once
#include "../element/Element.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>
#include <vector>



namespace Chess::Rendering::Elements {

class ChessBoard {

private:
  /// @brief Stores all board squares
  std::vector<Rectangle *> squares;

public:
  const int SQUARE_WIDTH = 150;
  const int SQUARE_HEIGHT = 100;

  SDL_Color light = {240, 217, 181, 255};
  SDL_Color dark = {181, 136, 99, 255};

  ChessBoard();
  /// @brief deconstructor
  ~ChessBoard(); // We might not need this, but just in case
};

} // namespace Chess::Rendering::Elements