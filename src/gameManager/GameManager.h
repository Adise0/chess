#pragma once
#include "../ui/screens/inGame/InGame.h"
#include "../ui/screens/mainMenu/MainMenu.h"
#include <SDL3/SDL.h>

namespace Chess {
using namespace Rendering::Screens;
class GameManager {
private:
  /// @brief Whether the game is runninng
  static bool isRunning;

public:
  static MainMenu mainMenu;
  static InGame inGame;

private:
  /// @brief Process user input
  /// @param event
  static void ProcessInput(SDL_Event &event);

  /// @brief Updates game logic each frame
  /// @param deltaTime Time elapsed since last frame
  static void Update(float deltaTime);

  /// @brief Renders the current game state
  static void Render();

  /// @brief Loads screens
  static void LoadScreens();


public:
  /// @brief Runs the main game loop
  static void Run();

  /// @brief Starts the game
  static void StartGame();
};
} // namespace Chess
