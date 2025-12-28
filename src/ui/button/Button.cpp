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

void Button::HandleEvent(
    const SDL_Event
        &event) { // Isn't this checking if the button was pressed? Why the else if below?
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if (event.button.button ==
        SDL_BUTTON_LEFT) { // Why button.button, where are those buttons coming from?
      if (IsWithinRect((int)event.button.x,
                       (int)event.button.y)) { // IsWithinRect is giving me error
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


void Button::
    Render() { // So to override means to fuck the other's code and do the fuck we want with it?
  SDL_Color currentColor =
      isPressed ? pressedColor
                : normalColor; // if isPressed is true, currentColor is pressedColor, else is else.
  color = currentColor;
  Rectangle::Render();
}
} // namespace Chess::Rendering::Elements