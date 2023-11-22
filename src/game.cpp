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
/**
 * @brief Enumeration representing room types
 */
enum RoomType {
    ROOM,     /**< Room */
    CORRIDOR,   /**< Corridor */
};

const unsigned int WINDOW_WIDTH = 800u;
const unsigned int WINDOW_HEIGHT = 600u;

const int ROOM_AMOUNT = 20;
const int TILE_SIZE = 1;

const float ZOOM_LEVEL = 5.0f;

class Game {
public:
    Game() {
        initializeWindow();
        initiateDungeon();
        initializeCircle();
        //initiateInventory();
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
        circle.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            // Handle other input events (keyboard, mouse, etc.)

            // Handle keyboard player movement
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                sf::Keyboard::Key key = event.key.code;
                moveUp = (key == sf::Keyboard::W) ? (event.type == sf::Event::KeyPressed) : moveUp;
                moveDown = (key == sf::Keyboard::S) ? (event.type == sf::Event::KeyPressed) : moveDown;
                moveLeft = (key == sf::Keyboard::A) ? (event.type == sf::Event::KeyPressed) : moveLeft;
                moveRight = (key == sf::Keyboard::D) ? (event.type == sf::Event::KeyPressed) : moveRight;
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
        sf::View view = window.getView();
        view.setCenter(circle.getPosition());

        view.setSize(window.getDefaultView().getSize() / ZOOM_LEVEL);

        window.setView(view);
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
        srand(4);
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
            drawRoom(room, ROOM);
        }
        for (const Room& corridor : corridors) {
            drawRoom(corridor, CORRIDOR);
        }
    }

    void drawRoom(const Room& room, RoomType type) {
        for (int i = 0; i < abs(room.width); ++i) {
            for (int j = 0; j < abs(room.height); ++j) {
                sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tileShape.setPosition(sf::Vector2f((room.x + i) * TILE_SIZE, (room.y + j) * TILE_SIZE));

                switch (type)
                {
                case ROOM:
                    tileShape.setFillColor(room.tileColors[i][j]);
                    break;
                case CORRIDOR:
                    tileShape.setFillColor(sf::Color(255, 0, 0));
                    break;
                default:
                    tileShape.setFillColor(sf::Color(255, 0, 0));
                    break;
                }
                
                window.draw(tileShape);
            }
        }
    }
};