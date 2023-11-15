#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "dungeon.cpp"
#include "item.cpp"

/*
TODO: Create some sort of tests here to check whether items, dungeons etc
      are working properly as discussed with the project advisor
*/

const std::string WINDOW_TITLE = "Dungeon Crawler";

const unsigned int WINDOW_WIDTH = 800u;
const unsigned int WINDOW_HEIGHT = 600u;

const int ROOM_AMOUNT = 10;
const int ROOM_MAX_WIDTH = 800;
const int ROOM_MAX_HEIGHT = 600;

class Game {
public:
    Game() {
        initializeWindow();
        initiateDungeon();
        initializeCircle();
        initiateInventory();
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

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

    void initializeWindow() {
        sf::Vector2u windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        window.create(sf::VideoMode(windowSize), WINDOW_TITLE);
        window.setFramerateLimit(60);
        window.setPosition(sf::Vector2i(0, 0));
    }

    void initializeCircle() {
        circle.setRadius(10);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(sf::Vector2f(100u, 300u));
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            // Handle other input events (keyboard, mouse, etc.)
            if (event.type == sf::Event::KeyPressed) {
                sf::Keyboard::Key key = event.key.code;
                if (key == sf::Keyboard::W) {
                    moveUp = true;
                } else if (key == sf::Keyboard::S) {
                    moveDown = true;
                } else if (key == sf::Keyboard::A) {
                    moveLeft = true;
                } else if (key == sf::Keyboard::D) {
                    moveRight = true;
                }
            } else if (event.type == sf::Event::KeyReleased) {
                sf::Keyboard::Key key = event.key.code;
                if (key == sf::Keyboard::W) {
                    moveUp = false;
                } else if (key == sf::Keyboard::S) {
                    moveDown = false;
                } else if (key == sf::Keyboard::A) {
                    moveLeft = false;
                } else if (key == sf::Keyboard::D) {
                    moveRight = false;
                }
            }
        }
    }

    void update() {
        // Update game objects, handle collisions, implement game logic
        // Update player, enemies, levels, etc.
        sf::Vector2f movement(0, 0);
        if (moveUp) {
            movement.y -= circleSpeed;
        }
        if (moveDown) {
            movement.y += circleSpeed;
        }
        if (moveLeft) {
            movement.x -= circleSpeed;
        }
        if (moveRight) {
            movement.x += circleSpeed;
        }
        circle.move(movement);

    }

    void render() {
        window.clear();
        // Render dungeon, game objects, UI elements, etc.

        // Render the moving object (circle)
        window.draw(circle);

        // Render the dungeon
        drawDungeon();

        window.display();
    }

    void initiateDungeon() {
        dungeon.generateRooms(rooms, ROOM_AMOUNT, ROOM_MAX_WIDTH, ROOM_MAX_HEIGHT);
        dungeon.generateCorridors(rooms, corridors);
    }

    void initiateInventory() {
        Item item1("Sword", 2);
        Item item2("Potion", 5);
        Item item3("Armor", 1);

        inventory.addItem(item1);
        inventory.addItem(item2);
        inventory.addItem(item3);

        // Print the inventory
        inventory.printInventory();
    }

    void drawDungeon() {
        for (const Room& room : rooms) {
            drawRoom(room);
        }
        for (const Room& corridor : corridors) {
            drawRoom(corridor);
        }
    }

    void drawRoom(const Room& room) {
        for (int i = 0; i < room.width; ++i) {
            for (int j = 0; j < room.height; ++j) {
                sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tileShape.setPosition(sf::Vector2f((room.x + i) * TILE_SIZE, (room.y + j) * TILE_SIZE));
                tileShape.setTexture(&room.tileTextures[i][j]);
                window.draw(tileShape);
            }
        }
    }
};