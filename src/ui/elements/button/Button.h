#pragma once
#include "../../../windowManager/WindowManager.h"
#include "../element/Element.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>
#include <functional>

namespace Chess::Rendering::Elements {

class Button : public Rectangle {

public:
  /// @brief The color when pressed
  SDL_Color pressedColor;
  /// @brief The base color when unpressed
  SDL_Color baseColor;

  /// @brief The OnClick listeners
  std::vector<std::function<void()>> onClickListeners;

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

  /// @brief Registers an onClick listener
  /// @param listener The listener to register
  void OnClick(std::function<void()> listener);

  void RemoveListeners();

  /// @brief Whether the button is currently being pressed
  bool isPressed;


private:
  /// @brief Gets the default pressed color
  /// @return The pressed color
  SDL_Color GetPressedColor();


  /// @brief Handles the on click event
  void OnClickEvent();
};
} // namespace Chess::Rendering::Elements
