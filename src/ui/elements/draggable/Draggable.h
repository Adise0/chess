#pragma once
#include "../../../windowManager/WindowManager.h"
#include "../element/Element.h"
#include "../rectangle/Rectangle.h"
#include <SDL3/SDL.h>
#include <functional>


namespace Chess::Rendering::Elements {

class Draggable : public Rectangle {

private:
  /// @brief The OnClick listeners
  std::vector<std::function<void()>> onClickListeners;
  /// @brief The OnDragStart listeners
  std::vector<std::function<void()>> onDragStartListeners;
  /// @brief The OnDragEnd listeners
  std::vector<std::function<void()>> onDragEndListeners;

public:
  /// @brief Creates a clickabale button
  /// @param rect The button rect
  /// @param color button base color
  Draggable(SDL_FRect rect, Renderer renderer);

  /// @brief Handles the button events
  /// @param event Reference to each event
  void HandleEvent(SDL_Event &event) override;

  /// @brief The overriden button render
  void Render() override;

  /// @brief Registers an onClick listener
  /// @param listener The listener to register
  void OnClick(std::function<void()> listener);

  /// @brief Registers an onDragStart listener
  /// @param listener The listener to register
  void OnDragStart(std::function<void()> listener);

  /// @brief Registers an onDragEnd listener
  /// @param listener The listener to register
  void OnDragEnd(std::function<void()> listener);

  /// @brief Whether the element is currently being pressed
  bool isPressed;
  /// @brief Whether the element is currently being dragged
  bool isBeingDragged;

private:
  /// @brief Handles the on click event
  void OnClickEvent();
  /// @brief Handles the on drag start event
  void OnDragStartEvent();
  /// @brief Handles the on drag end event
  void OnDragEndvent();
};
} // namespace Chess::Rendering::Elements
