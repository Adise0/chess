#pragma once
#include "../../windowManager/WindowManager.h"
#include "../element/Element.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>
#define SDL_BUTTON_LEFT 1

namespace Chess::Rendering::Elements {

class Button : public Rectangle {

public:
  /// @brief A clickabale button
  /// Inherits from rectangle to handle drawing and hit detection
  /// @param x x coordinate of the button
  /// @param y y coordinate of the button
  /// @param width button width
  /// @param height button height
  /// @param baseColor button base color
  Button(float x, float y, float width, float height, // This struct
         SDL_Color baseColor);


  /// @brief Handles all mouse events
  /// @param event Reference to each event
  void HandleEvent(const SDL_Event &event);


  void Render() override;


private:
  bool isPressed = false;
  SDL_Color normalColor;
  SDL_Color pressedColor;
};
} // namespace Chess::Rendering::Elements