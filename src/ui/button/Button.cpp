#include "Button.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>
#include <iostream>



namespace Chess::Rendering::Elements {

Button::Button(float x, float y, float width, float height, SDL_Color baseColor)
    : Rectangle({x, y, width, height}, baseColor) {
  normalColor = baseColor;

  // Making color darker
  pressedColor = {(Uint8)(baseColor.r * 0.7f), (Uint8)(baseColor.g * 0.7f),
                  (Uint8)(baseColor.b * 0.7f), baseColor.a};
}
void Button::HandleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      if (IsWithinRect((int)event.button.x, (int)event.button.y)) {
        isPressed = true;
      }
    }
  }

  else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      if (isPressed && IsWithinRect((int)event.button.x, (int)event.button.y)) {
        std::cout << "Button was pressed!";
      }
      isPressed = false;
    }
  }
}

/// @brief A button that changes its color when you press it
void Button::Render() {
  SDL_Color currentColor = isPressed ? pressedColor : normalColor;
  color = currentColor;
  Rectangle::Render();
}
} // namespace Chess::Rendering::Elements