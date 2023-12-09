#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "dungeon.hpp"
#include "inventory.hpp"
#include "textureManager.hpp"
#include "Creature/GameCharacter.hpp"
#include "gameOverScreen.hpp"

// Constants
const std::string WINDOW_TITLE = "Dungeon Crawler";
const unsigned int WINDOW_WIDTH = 1080u;
const unsigned int WINDOW_HEIGHT = 720u;
const int ROOM_AMOUNT = 5;
const int TILE_SIZE = 1;
const float ZOOM_LEVEL = 50.0f;

// Enum for room types
enum RoomType {
  ROOM,
  CORRIDOR,
};

/**
 * @brief The Game class manages the main game loop and logic.
 */
class Game {
 public:
  Game(); ///< Constructor
  ~Game(); ///< Destructor
  void Run(); ///< Start the game loop

 private:
  /// @brief main character (me like literally)
  Player player_; ///< Main character
  std::vector<Monster *> monsters_; ///< List of monsters
  std::vector<sf::Vector2f> potions_; ///< List of potions_

  sf::RenderWindow window_; ///< Render window

  Dungeon dungeon_; ///< Dungeon generator
  Inventory inventory_; ///< Game inventory_
  GameOverScreen gameOverScreen_; ///< Game over screen
  std::vector<Room> rooms_; ///< List of rooms_
  std::vector<Room> corridors_; ///< List of corridors_

  // Movement flags
  bool moveUp_ = false;
  bool moveDown_ = false;
  bool moveLeft_ = false;
  bool moveRight_ = false;
  bool isRunning_ = false;
  bool gameWon_ = false;
  bool gameLost_ = false;

  // Methods
  static void InitializeTextures(); ///< Load textures
  bool CheckWinning(bool monstersKilled); ///< Check for winning condition
  bool CheckLosing(); ///< Check for losing condition
  void InitializeWindow(); ///< Initialize game window
  void ProcessEvents(); ///< Process user input events
  void Update(); ///< Update game logic
  void Render(); ///< Render game elements
  void InitiateDungeon(); ///< Generate dungeon_ layout
  void InitiateInventory(); ///< Initialize inventory_ items
  void DrawDungeon(); ///< Draw dungeon_ layout
  void DrawRoom(const Room &room, RoomType type); ///< Draw a room
};

#endif /* GAME_HPP */
