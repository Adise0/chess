#pragma once
#include <SDL3/SDL.h>
namespace Chess::Rendering::Elements {

class Rectangle {

public:
  /// @brief The base color
  SDL_Color color;
  /// @brief The rect
  SDL_Rect rect;
  /// @brief The sorting layer (z-index)
  short sortingLayer;
  /// @brief Whether the mouse is hovering this object
  bool isHovering;

public:
  /// @brief Creates a new rectangle
  /// @param rect The rect to use
  Rectangle(SDL_Rect rect, SDL_Color color) : rect(rect), color(color) {}

  /// @brief Sets the position of the rectangle
  /// @param x The new x
  /// @param y The new y
  void SetPosition(int x, int y);

private:
  /// @brief Checks if the position is within the rectangle
  /// @param x The x coord
  /// @param y The y coord
  /// @return Whether it is inside the rectangle
  bool IsWithinRect(int x, int y);

  void Render(SDL_Surface *surface) {

    // SDL_FillSurfaceRect(surface, &rect, SDL_MapRGB(Fmt, nullptr, r, g, b));
  }
};
} // namespace Chess::Rendering::Elements
