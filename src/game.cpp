#include "game.hpp"

/*
TODO: Create some sort of tests here to check whether items, dungeons etc
      are working properly as discussed with the project advisor
*/


Game::Game() {
    initializeWindow();
    initiateDungeon();
    initializeCircle();
    //initiateInventory();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::initializeWindow() {
    sf::Vector2u windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.create(sf::VideoMode(windowSize), WINDOW_TITLE);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));
}

void Game::initializeCircle() {
    circle.setRadius(10);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
}

void Game::processEvents() {
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

void Game::update() {
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

void Game::render() {
    window.clear();
    window.draw(circle);
    drawDungeon();
    window.display();
}

void Game::initiateDungeon() {
    srand(4);
    dungeon.generateDungeon(rooms, corridors, ROOM_AMOUNT, TILE_SIZE, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::initiateInventory() {
    Item item1("Sword", 2);
    Item item2("Potion", 5);
    Item item3("Armor", 1);

    inventory.addItem(item1);
    inventory.addItem(item2);
    inventory.addItem(item3);

    inventory.printInventory();
}

void Game::drawDungeon() {
    for (const Room& room : rooms) {
        drawRoom(room, ROOM);
    }
    for (const Room& corridor : corridors) {
        drawRoom(corridor, CORRIDOR);
    }
}

void Game::drawRoom(const Room& room, RoomType type) {
    for (int i = 0; i < abs(room.width); ++i) {
        for (int j = 0; j < abs(room.height); ++j) {
            sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tileShape.setPosition(sf::Vector2f((room.x + i) * TILE_SIZE, (room.y + j) * TILE_SIZE));

            switch (type) {
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

