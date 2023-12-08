#include "game.hpp"

const std::string TEXTURES_PATH = "../assets/textures/";
sf::Texture room_t1;
sf::Texture room_t2;
sf::Texture corridor_t1;
sf::Texture player_t;
sf::Texture assassin_t;
sf::Texture boss_t;
sf::Texture sword_inv_t;
sf::Texture potion_inv_t;
sf::Font font;
const float PLAYER_WALKING_SPEED = 0.12f;
const float PLAYER_RUNNING_SPEED = 0.16f;

Game::Game() : player_("Hooman", "Literally me", 50, PLAYER_RUNNING_SPEED,
                       sf::Vector2f(0, 0),
                       window, Room(0, 0, 0, 0, false), player_t) {
  initializeWindow();
  initializeTextures();
  initiateDungeon();
  player_.SetRoom(rooms[0], monsters_, potions_);
  player_.SetTexture(player_t);
  std::vector<Room> allRooms;
  for (int i = 0; i + 1 < rooms.size(); i++) {
    allRooms.push_back(rooms[i]);
    allRooms.push_back(corridors[i]);
  }
  allRooms.push_back(rooms.back());
  player_.SetRooms(allRooms);
  player_.SetPosition(sf::Vector2f(rooms[0].x + rooms[0].width / 2.0, rooms[0].y + rooms[0].height / 2.0));
  initiateInventory();
}

Game::~Game() {
  rooms.clear();
  corridors.clear();
  for (auto m : monsters_) {
    delete m;
  }
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    update();
    if (!gameWon && !gameLost) {
      render();
    }
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
  if (!sword_inv_t.loadFromFile(TEXTURES_PATH + "sword_inv.png")) {
    std::cerr << "Error loading sword_inv.png" << std::endl;
    return;
  }
  if (!potion_inv_t.loadFromFile(TEXTURES_PATH + "potion_inv.png")) {
    std::cerr << "Error loading potion_inv.png" << std::endl;
    return;
  }
  if (!font.loadFromFile(TEXTURES_PATH + "Amatic-Bold.ttf")) {
    std::cerr << "Error loading Font" << std::endl;
    return;
  }
  if (!boss_t.loadFromFile(TEXTURES_PATH + "boss.png")) {
    std::cerr << "Error loading Boss (boss.png)" << std::endl;
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
    // Handle other input events (keyboard, mouse, etc.)

    // Handle keyboard player movement
    if (event.type == sf::Event::KeyPressed
        || event.type == sf::Event::KeyReleased) { // todo: maybe refactor movement logic to isKeyPressed
      sf::Keyboard::Key key = event.key.code;
      moveUp = (key == sf::Keyboard::W) ? (event.type == sf::Event::KeyPressed) : moveUp;
      moveDown = (key == sf::Keyboard::S) ? (event.type == sf::Event::KeyPressed) : moveDown;
      moveLeft = (key == sf::Keyboard::A) ? (event.type == sf::Event::KeyPressed) : moveLeft;
      moveRight = (key == sf::Keyboard::D) ? (event.type == sf::Event::KeyPressed) : moveRight;

      if (key == sf::Keyboard::LShift || key == sf::Keyboard::RShift) {
        isRunning = (event.type == sf::Event::KeyPressed);
      }

      if (sf::Keyboard::Num1 <= key && key <= sf::Keyboard::Num9) {
        player_.SetItemInUse(key - sf::Keyboard::Num1);
      }

      if (key == sf::Keyboard::E && event.type == sf::Event::KeyPressed) {
        player_.tryHealing();
      }

      if (key == sf::Keyboard::F && event.type == sf::Event::KeyPressed) {
        player_.TryPickup(potions_);
      }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
      player_.TryAttack(monsters_);
    }

    // Handle mouse click on "Play Again" button
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      sf::FloatRect buttonBounds = gameOverScreen.getPlayAgainButton().getGlobalBounds();
      auto translated_pos = window.mapPixelToCoords(mousePos); // Mouse position translated into world coordinates

      // Check if the click is within the button bounds
      if (buttonBounds.contains(sf::Vector2f(translated_pos))) {
        window.close();
        Game game;
        game.run();
      }
    }

  }
}

void Game::update() {
  bool monstersKilled = true;
  for (auto m : monsters_) {
    if (m->IsAlive()) {
      monstersKilled = false;
    }
  }
  if (checkWinning(monstersKilled)) {
    gameWon = true;
    return;
  }
  if (checkLosing()) {
    gameLost = true;
    return;
  }
  
  sf::Vector2f movement(
      moveRight ? 1 : (moveLeft ? -1 : 0.f),
      moveDown ? 1 : (moveUp ? -1 : 0.f)
  );
  player_.SetVelocity(movement *= (isRunning ? PLAYER_RUNNING_SPEED : PLAYER_WALKING_SPEED));

  sf::View view = window.getView();
  view.setCenter(player_.getPosition());
  view.setSize(window.getDefaultView().getSize() / ZOOM_LEVEL);
  window.setView(view);
  player_.SetMonstersCleared(monstersKilled);
  player_.Update(monsters_, potions_);
  for (auto m : monsters_) {
    m->tick(player_);
    m->Update();
  }
}

bool Game::checkWinning(bool monstersKilled) {
  if (player_.getRoomIndex() == rooms.size() + corridors.size() - 1 && monstersKilled) {
        gameOverScreen.render(window, font, "Congratulations! You won!", sf::Color::Green, sf::Color::Blue);
        return true;
  } 
  return false;
}

bool Game::checkLosing() {
  if (!player_.IsAlive()) {
        gameOverScreen.render(window, font, "You died! Game over!", sf::Color::Red, sf::Color::Red);
        return true;
  } 
  return false;
}

void Game::render() {
  window.clear();
  drawDungeon();
  player_.Draw();
  player_.GetInventory().Draw(window, player_.GetItemInUse());
  player_.DrawHealthBar(window);
  for (auto m : monsters_) {
    m->Draw();
    m->DrawHealthBar(window);
  }
  for (auto p : potions_) {
    Item::Draw(window, p, 1, potion_inv_t);
  }
  window.display();
}

void Game::initiateDungeon() {
  dungeon.generateDungeon(rooms, corridors, ROOM_AMOUNT, TILE_SIZE, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::initiateInventory() {
  player_.GetInventory().addSword(Sword("Escalibur", 1.2), 1);
  player_.GetInventory().addPotion(HealthPotion(), 3);
}

void Game::drawDungeon() {
  for (const Room &room : rooms) {
    drawRoom(room, ROOM);
  }
  for (const Room &corridor : corridors) {
    drawRoom(corridor, CORRIDOR);
  }
}

void Game::drawRoom(const Room &room, RoomType type) {
  for (int i = 0; i < abs(room.width); ++i) {
    for (int j = 0; j < abs(room.height); ++j) {
      sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
      tileShape.setPosition(sf::Vector2f((room.x + i) * TILE_SIZE, (room.y + j) * TILE_SIZE));

      switch (type) {
        case ROOM:tileShape.setTexture(room.tileTextures[i][j]);
          break;
        case CORRIDOR:tileShape.setTexture(&corridor_t1);
          break;
        default:tileShape.setTexture(room.tileTextures[i][j]);
          break;
      }

      window.draw(tileShape);
    }
  }
}

