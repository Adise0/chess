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
  std::vector<std::function<void(float x, float y)>> onDragEndListeners;

  /// @brief The drag start X position
  int dragStartX;
  /// @brief The drag start Y position
  int dragStartY;

  /// @brief The renderer rect
  SDL_FRect rendererRect;

public:
  /// @brief Whether the element is currently being pressed
  bool isPressed;
  /// @brief Whether the element is currently being dragged
  bool isBeingDragged;

public:
  /// @brief Creates a draggable element
  /// @param rect The draggable rect
  /// @param rendererRect The draggable rect for the renderer
  Draggable(SDL_FRect rect, SDL_FRect rendererRect, Renderer renderer);

  /// @brief Handles the draggable events
  /// @param event Reference to each event
  void HandleEvent(SDL_Event &event) override;

  /// @brief The overriden draggable render
  void Render() override;

  /// @brief Registers an onClick listener
  /// @param listener The listener to register
  void OnClick(std::function<void()> listener);

  /// @brief Registers an onDragStart listener
  /// @param listener The listener to register
  void OnDragStart(std::function<void()> listener);

  /// @brief Registers an onDragEnd listener
  /// @param listener The listener to register
  void OnDragEnd(std::function<void(float x, float y)> listener);

private:
  /// @brief Handles the on click event
  void OnClickEvent();
  /// @brief Handles the on drag start event
  void OnDragStartEvent();
  /// @brief Handles the on drag end event
  void OnDragEndEvent();
};
} // namespace Chess::Rendering::Elements
