#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "dungeon.hpp"
#include "inventory.hpp"
#include "textureManager.hpp"
#include "Creature/GameCharacter.hpp"

const std::string WINDOW_TITLE = "Dungeon Crawler";
const unsigned int WINDOW_WIDTH = 800u;
const unsigned int WINDOW_HEIGHT = 600u;
const int ROOM_AMOUNT = 5;
const int TILE_SIZE = 1;
const float ZOOM_LEVEL = 50.0f;

enum RoomType {
  ROOM,
  CORRIDOR,
};

class Game {
 public:
  Game();
  ~Game();
  void run();

 private:
  /// @brief main character (me like literally)
  Player player_;
  std::vector<Monster *> monsters_;
  std::vector<sf::Vector2f> potions_;

  sf::RenderWindow window;
  sf::CircleShape circle;

  Dungeon dungeon;
  Inventory inventory;
  std::vector<Room> rooms;
  std::vector<Room> corridors;

  bool moveUp = false;
  bool moveDown = false;
  bool moveLeft = false;
  bool moveRight = false;
  bool isRunning = false;

  float circleSpeed = 0.3f;

  void initializeTextures();
  void initializeWindow();
  void initializeCircle();
  void processEvents();
  void update();
  void render();
  void initiateDungeon();
  void initiateInventory();
  void drawDungeon();
  void addItem(Item newItem);
  void drawRoom(const Room &room, RoomType type);
};

#endif /* GAME_HPP */
