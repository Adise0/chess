#pragma once
#include "../../windowManager/WindowManager.h"
#include "../element/Element.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>

#define SDL_BUTTON_LEFT 1

namespace Chess::Rendering::Elements {

class Button : public Rectangle {

public:
  Button(float x, float y, float width, float height,
         SDL_Color baseColor); // So this is a struct? Why is it written like a function?

  void HandleEvent(const SDL_Event &event);

  void Render() override;


private:
  bool isPressed = false;
  SDL_Color normalColor;
  SDL_Color pressedColor;
};
} // namespace Chess::Rendering::Elements