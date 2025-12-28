#include "Button.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <windows.h>


namespace Chess::Rendering::Elements {



Button::Button(SDL_FRect rect, SDL_Color color) : Rectangle(rect, color) {
  baseColor = color;
  pressedColor = GetPressedColor();
  isPressed = false;
}

void Button::HandleEvent(SDL_Event &event) {
  // #region HandleEvent
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
    if (IsWithinRect(event.button.x, event.button.y)) isPressed = true;

  }

  else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
    if (isPressed) isPressed = false;
  }
  // #endregion
}


void Button::Render() {
  // #region Render
  color = isPressed ? pressedColor : baseColor;
  Rectangle::Render();
  // #endregion
}


SDL_Color Button::GetPressedColor() {
  // #region GetPressedColor
  return {(Uint8)(color.r * 0.7f), (Uint8)(color.g * 0.7f), (Uint8)(color.b * 0.7f), color.a};
  // #endregion
}

} // namespace Chess::Rendering::Elements
