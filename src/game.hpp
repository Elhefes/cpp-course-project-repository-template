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
  void run(); ///< Start the game loop

private:
    /// @brief main character (me like literally)
    Player player_; ///< Main character
    std::vector<Monster *> monsters_; ///< List of monsters
    std::vector<sf::Vector2f> potions_; ///< List of potions
    
    sf::RenderWindow window; ///< Render window

    Dungeon dungeon; ///< Dungeon generator
    Inventory inventory; ///< Game inventory
    GameOverScreen gameOverScreen; ///< Game over screen
    std::vector<Room> rooms; ///< List of rooms
    std::vector<Room> corridors; ///< List of corridors

    // Movement flags
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;
    bool isRunning = false;
    bool gameWon = false;
    bool gameLost = false;

    // Methods
    void initializeTextures(); ///< Load textures
    bool checkWinning(bool monstersKilled); ///< Check for winning condition
    bool checkLosing(); ///< Check for losing condition
    void initializeWindow(); ///< Initialize game window
    void initializeCircle(); ///< Initialize circle
    void processEvents(); ///< Process user input events
    void update(); ///< Update game logic
    void render(); ///< Render game elements
    void initiateDungeon(); ///< Generate dungeon layout
    void initiateInventory(); ///< Initialize inventory items
    void drawDungeon(); ///< Draw dungeon layout
    void addItem(Item newItem); ///< Add an item to the inventory
    void drawRoom(const Room& room, RoomType type); ///< Draw a room
};

#endif /* GAME_HPP */
