#pragma once
#include <SDL3/SDL.h>
namespace Chess::Rendering {
class WindowManager {
private:
  /// @brief The SDL window instance
  static SDL_Window *window;

public:
  /// @brief The SDL renderer instance
  static SDL_Renderer *renderer;

public:
  /// @brief Creates and initializes the window manager
  static void InitializeWindow();

  /// @brief Disposes and cleans the window manager
  static void Dispose();
};
} // namespace Chess::Rendering
