#pragma once
#include "../ui/screens/byebyeScreen/ByebyeMenu.h"
#include "../ui/screens/inGame/InGame.h"
#include "../ui/screens/mainMenu/MainMenu.h"
#include "../ui/screens/supersayanPawn/SupersayanPawn.h"
#include <SDL3/SDL.h>
#include <vector>

namespace Chess {
using namespace Rendering::Screens;
class GameManager {
private:
  /// @brief Whether the game is runninng
  static bool isRunning;

public:
  /// @brief The main menu screen
  static MainMenu mainMenu;
  /// @brief The in-game screen
  static InGame inGame;

  // /// @brief The byebye menu
  static ByebyeMenu byebyeMenu;

  // /// @brief Yes
  static SupersayanPawn supersayanPawn;

private:
  /// @brief Process user input
  /// @param event
  static void ProcessInput(SDL_Event &event);

  /// @brief Updates game logic each frame
  /// @param deltaTime Time elapsed since last frame
  static void Update(float deltaTime);

  /// @brief Renders the presented screens
  static void Render();

  /// @brief Sorts the element vector by their sorting layer. IN PLACE
  /// @param  elements The vector to sort
  static void SortElements(std::vector<Element *> &elements);

  /// @brief Loads screens
  static void LoadScreens();


public:
  /// @brief Runs the main game loop
  static void Run();

  /// @brief Starts the game
  static void StartGame();
};
} // namespace Chess
