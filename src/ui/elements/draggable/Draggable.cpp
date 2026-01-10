#include "Draggable.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <windows.h>


namespace Chess::Rendering::Elements {

Draggable::Draggable(SDL_FRect rect, Renderer renderer) : Rectangle(rect, renderer) {
  // #region Draggable
  isPressed = false;
  isBeingDragged = false;
  // #endregion
}

void Draggable::HandleEvent(SDL_Event &event) {
  // #region HandleEvent
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
    if (IsWithinRect(event.button.x, event.button.y)) {
      isPressed = true;
      dragStartX = event.button.x - rect.x;
      dragStartY = event.button.y - rect.y;
    }
  }

  if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
    if (isPressed) {
      isPressed = false;
      if (isBeingDragged) {
        OnDragEndEvent();
        isBeingDragged = false;
      } else {
        OnClickEvent();
      }
    }
  }

  if (event.type == SDL_EVENT_MOUSE_MOTION) {
    if (isPressed) {
      if (!isBeingDragged) OnDragStartEvent();
      isBeingDragged = true;
      rect.x = event.motion.x - dragStartX;
      rect.y = event.motion.y - dragStartY;
    }
  }
  // #endregion
}

void Draggable::Render() {
  // #region Render
  Texture textureType = Texture::base;
  if (isPressed) textureType = Texture::pressed;

  renderer.Render(rect, textureType);
  // #endregion
}

void Draggable::OnClick(std::function<void()> listener) {
  // #region OnClick
  onClickListeners.push_back(listener);
  // #endregion
}
void Draggable::OnDragStart(std::function<void()> listener) {
  // #region OnDragStart
  onDragStartListeners.push_back(listener);
  // #endregion
}
void Draggable::OnDragEnd(std::function<void(float x, float y)> listener) {
  // #region OnDragEnd
  onDragEndListeners.push_back(listener);
  // #endregion
}

void Draggable::OnClickEvent() {
  // #region OnClickEvent
  for (const std::function<void()> &listener : onClickListeners) {
    listener();
  }
  // #endregion
}

void Draggable::OnDragStartEvent() {
  // #region OnDragStartEvent
  for (const std::function<void()> &listener : onDragStartListeners) {
    listener();
  }
  // #endregion
}

void Draggable::OnDragEndEvent() {
  // #region OnDragEndEvent
  for (const std::function<void(float x, float y)> &listener : onDragEndListeners) {
    listener(rect.x, rect.y);
  }
  // #endregion
}


} // namespace Chess::Rendering::Elements
