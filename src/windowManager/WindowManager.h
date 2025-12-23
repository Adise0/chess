#include <SDL3/SDL.h>

namespace Chess::Rendering {
class WindowManager {
private:
  /// @brief The SDL renderer instance
  static SDL_Renderer *renderer;
  /// @brief The SDL window instance
  static SDL_Window *window;
  /// @brief Whether the window is running
  static bool isRunning;

public:
  /// @brief Creates and initializes the window manager
  static void CreateChessWindow();

  /// @brief Runs the window loop
  static void RunWindow();

  /// @brief Disposes and cleans the window manager
  static void Dispose();
};
} // namespace Chess::Rendering
