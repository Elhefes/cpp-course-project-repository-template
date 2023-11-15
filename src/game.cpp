#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "dungeon.cpp"
#include "item.cpp"

/*
TODO: Create some sort of tests here to check whether items, dungeons etc
      are working properly as discussed with the project advisor
*/

const unsigned int WINDOW_WIDTH = 800u;
const unsigned int WINDOW_HEIGHT = 600u;

const int ROOM_AMOUNT = 100;
const int TILE_SIZE = 1;

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

    void initializeWindow() {
        sf::Vector2u windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        window.create(sf::VideoMode(windowSize), "Dungeon Crawler");
        window.setFramerateLimit(60);
    }

    void initializeCircle() {
        circle.setRadius(20);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(sf::Vector2f(100u, 300u));
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle other input events (keyboard, mouse, etc.)
        }
    }

    void update() {
        // Update game objects, handle collisions, implement game logic
        // Update player, enemies, levels, etc.

        // Example: Move the circle to the right
        sf::Vector2f newPosition = circle.getPosition();
        newPosition.x += 1;
        circle.setPosition(newPosition);
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
        srand(3);
        dungeon.generateDungeon(rooms, corridors, ROOM_AMOUNT, TILE_SIZE, WINDOW_WIDTH, WINDOW_HEIGHT);
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
            drawC(corridor);
        }
    }

    void drawRoom(const Room& room) {
        for (int i = 0; i < room.width; ++i) {
            for (int j = 0; j < room.height; ++j) {
                sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tileShape.setPosition(sf::Vector2f((room.x + i) * TILE_SIZE, (room.y + j) * TILE_SIZE));
                tileShape.setFillColor(room.tileColors[i][j]);
                window.draw(tileShape);
            }
        }
    }

    void drawC(const Room& room) {
        for (int i = 0; i < abs(room.width); ++i) {
            for (int j = 0; j < abs(room.height); ++j) {
                sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tileShape.setPosition(sf::Vector2f((room.x + i) * TILE_SIZE, (room.y + j) * TILE_SIZE));
                tileShape.setFillColor(sf::Color(255, 0, 0));
                window.draw(tileShape);
            }
        }
    }
};