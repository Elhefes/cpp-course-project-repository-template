#include "game.hpp"

/*
TODO: Create some sort of tests here to check whether items, dungeons etc
      are working properly as discussed with the project advisor
*/
const std::string TEXTURES_PATH = "../assets/textures/";
sf::Texture room_t1;
sf::Texture room_t2;
sf::Texture corridor_t1;
sf::Texture player_t;
sf::Texture assassin_t;
const float PLAYER_WALKING_SPEED = 0.25f;
const float PLAYER_RUNNING_SPEED = 0.4f;

Game::Game() : player_("Hooman", "Literally me", 50, PLAYER_WALKING_SPEED,
                      sf::Vector2f(0, 0),
                      window, Room(0, 0, 0, 0, false)) {
    initializeWindow();
    initializeTextures();
    initiateDungeon();
    player_.UpdateRooms(rooms);
    player_.UpdateCorridors(corridors);
    //initiateInventory();
    player_.SetRoom(rooms[0], monsters_);
    player_.SetPosition(sf::Vector2f(rooms[0].x + rooms[0].width / 2.0, rooms[0].y + rooms[0].height / 2.0));
}

Game::~Game() {
    rooms.clear();
    corridors.clear();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::initializeTextures() {
    if (!room_t1.loadFromFile(TEXTURES_PATH + "room_floor1.png")) {
        std::cerr << "Error loading room_floor1.png" << std::endl;
        return;
    }
        if (!room_t2.loadFromFile(TEXTURES_PATH + "room_floor2.png")) {
        std::cerr << "Error loading room_floor2.png" << std::endl;
        return;
    }
        if (!corridor_t1.loadFromFile(TEXTURES_PATH + "corridor_floor1.png")) {
        std::cerr << "Error loading corridor_floor1.png" << std::endl;
        return;
    }
        if (!player_t.loadFromFile(TEXTURES_PATH + "player.png")) {
        std::cerr << "Error loading player.png" << std::endl;
        return;
    }
        if (!assassin_t.loadFromFile(TEXTURES_PATH + "assassin.png")) {
        std::cerr << "Error loading assassin.png" << std::endl;
        return;
    }
}

void Game::initializeWindow() {
    sf::Vector2u windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.create(sf::VideoMode(windowSize), WINDOW_TITLE);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        sf::Event::EventType type = event.type;
        if (type == sf::Event::KeyPressed || type == sf::Event::KeyReleased) {
            sf::Keyboard::Key key = event.key.code;
            moveUp = (key == sf::Keyboard::W) ? (type == sf::Event::KeyPressed) : moveUp;
            moveDown = (key == sf::Keyboard::S) ? (type == sf::Event::KeyPressed) : moveDown;
            moveLeft = (key == sf::Keyboard::A) ? (type == sf::Event::KeyPressed) : moveLeft;
            moveRight = (key == sf::Keyboard::D) ? (type == sf::Event::KeyPressed) : moveRight;

            if (key == sf::Keyboard::LShift || key == sf::Keyboard::RShift) {
                isRunning = (event.type == sf::Event::KeyPressed);
            }
        }
    }
}

void Game::update() {
    sf::Vector2f movement(
      moveRight ? 1 : (moveLeft ? -1 : 0.f),
      moveDown ? 1 : (moveUp ? -1 : 0.f)
    );
    movement *= player_.GetMaxVelocity();
    player_.SetVelocity(movement *= (isRunning ? PLAYER_RUNNING_SPEED : PLAYER_WALKING_SPEED));

    sf::View view = window.getView();
    view.setCenter(player_.getPosition());
    view.setSize(window.getDefaultView().getSize() / ZOOM_LEVEL);
    window.setView(view);
    bool monstersKilled = false;
    if (monsters_.size() == 1) {
        monstersKilled = true;
    }
    player_.Update(monstersKilled);
    for (auto m : monsters_) {
        m->tick(player_);
        m->Update(monstersKilled);
    }
}

void Game::render() {
    window.clear();
    drawDungeon();
    window.draw(circle);
    player_.Draw();
    for (auto m : monsters_) {
        auto pos = m->GetPosition();
        auto rx = m->GetRoom().x;
        auto ry = m->GetRoom().x;
        auto rw = m->GetRoom().width;
        auto rh = m->GetRoom().height;
        m->Draw();
    }
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
                    tileShape.setTexture(room.tileTextures[i][j]);
                    break;
                case CORRIDOR:
                    tileShape.setTexture(&corridor_t1);
                    break;
                default:
                    tileShape.setTexture(room.tileTextures[i][j]);
                    break;
            }

            window.draw(tileShape);
        }
    }
}

