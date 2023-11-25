#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "dungeon.hpp"
#include "item.cpp"

const std::string WINDOW_TITLE = "Dungeon Crawler";
const unsigned int WINDOW_WIDTH = 800u;
const unsigned int WINDOW_HEIGHT = 600u;
const int ROOM_AMOUNT = 20;
const int TILE_SIZE = 1;
const float ZOOM_LEVEL = 5.0f;

enum RoomType {
    ROOM,
    CORRIDOR,
};

class Game {
public:
    Game();
    void run();

private:
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

    float circleSpeed = 1.0f;

    void loadTextures();
    void initializeWindow();
    void initializeCircle();
    void processEvents();
    void update();
    void render();
    void initiateDungeon();
    void initiateInventory();
    void drawDungeon();
    void drawRoom(const Room& room, RoomType type);
};

#endif /* GAME_HPP */
