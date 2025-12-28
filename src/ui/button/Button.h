#pragma once
#include "../../windowManager/WindowManager.h"
#include "../element/Element.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>
#define SDL_BUTTON_LEFT 1

namespace Chess::Rendering::Elements {

class Button : public Rectangle {

private:
  /// @brief Whether the button is currently being pressed
  bool isPressed;

  /// @brief Whether the button is color-based
  bool hasColor;

  /// @brief The color when pressed
  SDL_Color pressedColor;
  /// @brief The base color when unpressed
  SDL_Color baseColor;

public:
  /// @brief Creates a clickabale button
  /// @param rect The button rect
  /// @param color button base color
  Button(SDL_FRect rect, Renderer renderer);

  /// @brief Handles the button events
  /// @param event Reference to each event
  void HandleEvent(SDL_Event &event) override;

  /// @brief The overriden button render
  void Render() override;

private:
  /// @brief Gets the default pressed color
  /// @return The pressed color
  SDL_Color GetPressedColor();
};
} // namespace Chess::Rendering::Elements
