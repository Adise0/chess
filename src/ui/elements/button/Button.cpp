#include "Button.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <windows.h>


namespace Chess::Rendering::Elements {



Button::Button(SDL_FRect rect, Renderer renderer) : Rectangle(rect, renderer) {
  // #region Button

  if (hasColor) {
    baseColor = *renderer.color;
    pressedColor = GetPressedColor();
  }
  isPressed = false;
  // #endregion
}

void Button::HandleEvent(SDL_Event &event) {
  // #region HandleEvent
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
    if (IsWithinRect(event.button.x, event.button.y)) isPressed = true;

  }

  else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
    if (isPressed) {
      isPressed = false;
      if (IsWithinRect(event.button.x, event.button.y)) OnClickEvent();
    }
  }
  // #endregion
}

void Button::Render() {
  // #region Render
  if (hasColor) {
    renderer.color = &(isPressed ? pressedColor : baseColor);
    Rectangle::Render();
    return;
  }

  Texture textureType = Texture::base;
  if (isPressed) textureType = Texture::pressed;

  renderer.Render(rect, textureType);

  // #endregion
}

void Button::OnClick(std::function<void()> listener) {
  // #region OnClick
  onClickListeners.push_back(listener);
  // #endregion
}

void Button::OnClickEvent() {
  // #region OnClickEvent
  for (const std::function<void()> &listener : onClickListeners) {
    listener();
  }

  // #endregion
}

SDL_Color Button::GetPressedColor() {
  // #region GetPressedColor
  return {(Uint8)(baseColor.r * 0.7f), (Uint8)(baseColor.g * 0.7f), (Uint8)(baseColor.b * 0.7f),
          baseColor.a};
  // #endregion
}

} // namespace Chess::Rendering::Elements
