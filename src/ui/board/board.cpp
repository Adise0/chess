#include "board.h"

namespace Chess::Rendering::Elements {

ChessBoard::ChessBoard() {

  bool stop = false;
  float xPosition = 1200.0f / 8;
  float yPosition = 800.0f / 8;

  for (int i = 0; i < 8; i++) {
    xPosition = 80.0f; // Reset xPosition each row
    for (int j = 0; j < 8; j++) {
      SDL_FRect rect = {xPosition, yPosition, (float)SQUARE_WIDTH, (float)SQUARE_HEIGHT};
      SDL_Color currentColor = ((i + j) % 2 == 0) ? light : dark;
      Renderer renderer(&currentColor, nullptr, nullptr, nullptr);
      Rectangle *square = new Rectangle(rect, renderer);
      Element::elements.push_back(square);
      xPosition += SQUARE_WIDTH;
    }
    yPosition += SQUARE_HEIGHT;
  }
}

ChessBoard::~ChessBoard() { // For clean up
}

} // namespace Chess::Rendering::Elements