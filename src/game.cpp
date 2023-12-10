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

Game::Game() : player_("Hooman", "Literally me", 50, PLAYER_RUNNING_SPEED,
                       sf::Vector2f(0, 0),
                       window_, Room(0, 0, 0, 0, false), player_t) {
  InitializeWindow();
  InitializeTextures();
  InitiateDungeon();
  player_.SetRoom(rooms_[0], monsters_, potions_);
  player_.SetTexture(player_t);
  std::vector<Room> allRooms;
  for (int i = 0; i + 1 < rooms_.size(); i++) {
    allRooms.push_back(rooms_[i]);
    allRooms.push_back(corridors_[i]);
  }
  allRooms.push_back(rooms_.back());
  player_.SetRooms(allRooms);
  player_.SetPosition(sf::Vector2f(rooms_[0].x + rooms_[0].width / 2.0, rooms_[0].y + rooms_[0].height / 2.0));
  InitiateInventory();
}

Game::~Game() {
  rooms_.clear();
  corridors_.clear();
  for (auto m : monsters_) {
    delete m;
  }
}

void Game::Run() {
  while (window_.isOpen()) {
    ProcessEvents();
    Update();
    if (!gameWon_ && !gameLost_) {
      Render();
    }
  }
}

void Game::InitializeTextures() {
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

void Game::InitializeWindow() {
  sf::Vector2u windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  window_.create(sf::VideoMode(windowSize), WINDOW_TITLE);
  window_.setFramerateLimit(FRAMERATE_LIMIT);
  window_.setPosition(sf::Vector2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
}

void Game::ProcessEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
      window_.close();
    }
    // Handle other input events (keyboard, mouse, etc.)

    // Handle keyboard player movement
    if (event.type == sf::Event::KeyPressed
        || event.type == sf::Event::KeyReleased) { // todo: maybe refactor movement logic to isKeyPressed
      sf::Keyboard::Key key = event.key.code;
      moveUp_ = (key == sf::Keyboard::W) ? (event.type == sf::Event::KeyPressed) : moveUp_;
      moveDown_ = (key == sf::Keyboard::S) ? (event.type == sf::Event::KeyPressed) : moveDown_;
      moveLeft_ = (key == sf::Keyboard::A) ? (event.type == sf::Event::KeyPressed) : moveLeft_;
      moveRight_ = (key == sf::Keyboard::D) ? (event.type == sf::Event::KeyPressed) : moveRight_;

      if (key == sf::Keyboard::LShift || key == sf::Keyboard::RShift) {
        isRunning_ = (event.type == sf::Event::KeyPressed);
      }

      if (sf::Keyboard::Num1 <= key && key <= sf::Keyboard::Num9) {
        player_.SetItemInUse(key - sf::Keyboard::Num1);
      }

      if (key == sf::Keyboard::E && event.type == sf::Event::KeyPressed) {
        player_.TryHealing();
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
      sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
      sf::FloatRect buttonBounds = gameOverScreen_.GetPlayAgainButton().getGlobalBounds();
      auto translated_pos = window_.mapPixelToCoords(mousePos); // Mouse position translated into world coordinates

      // Check if the click is within the button bounds
      if (buttonBounds.contains(sf::Vector2f(translated_pos))) {
        window_.close();
        Game game;
        game.Run();
      }
    }

  }
}

void Game::Update() {
  bool monstersKilled = true;
  for (auto m : monsters_) {
    if (m->IsAlive()) {
      monstersKilled = false;
    }
  }
  if (CheckWinning(monstersKilled)) {
    gameWon_ = true;
    return;
  }
  if (CheckLosing()) {
    gameLost_ = true;
    return;
  }

  sf::Vector2f movement(
      moveRight_ ? 1 : (moveLeft_ ? -1 : 0.f),
      moveDown_ ? 1 : (moveUp_ ? -1 : 0.f)
  );
  player_.SetVelocity(movement *= (isRunning_ ? PLAYER_RUNNING_SPEED : PLAYER_WALKING_SPEED));

  sf::View view = window_.getView();
  view.setCenter(player_.GetPosition());
  view.setSize(window_.getDefaultView().getSize() / ZOOM_LEVEL);
  window_.setView(view);
  player_.SetMonstersCleared(monstersKilled);
  player_.Update(monsters_, potions_);
  for (auto m : monsters_) {
    m->tick(player_);
    m->Update();
  }
}

bool Game::CheckWinning(bool monstersKilled) {
  if (player_.GetRoomIndex() == rooms_.size() + corridors_.size() - 1 && monstersKilled) {
    gameOverScreen_.Render(window_, font, "Congratulations! You won!", sf::Color::Green, sf::Color::Blue);
    return true;
  }
  return false;
}

bool Game::CheckLosing() {
  if (!player_.IsAlive()) {
    gameOverScreen_.Render(window_, font, "You died! Game over!", sf::Color::Red, sf::Color::Red);
    return true;
  }
  return false;
}

void Game::Render() {
  window_.clear();
  DrawDungeon();
  player_.Draw();
  player_.GetInventory().Draw(window_, player_.GetItemInUse());
  player_.DrawHealthBar(window_);
  for (auto m : monsters_) {
    m->Draw();
    m->DrawHealthBar(window_);
  }
  for (auto p : potions_) {
    Item::Draw(window_, p, 1, potion_inv_t);
  }
  window_.display();
}

void Game::InitiateDungeon() {
  dungeon_.GenerateDungeon(rooms_, corridors_, ROOM_AMOUNT, TILE_SIZE, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::InitiateInventory() {
  player_.GetInventory().AddSword(Sword("Escalibur", START_SWORD_MULTIPLIER), 1);
  player_.GetInventory().AddPotion(HealthPotion(), INITIAL_POTION_NUMBER);
}

void Game::DrawDungeon() {
  for (const Room &room : rooms_) {
    DrawRoom(room, ROOM);
  }
  for (const Room &corridor : corridors_) {
    DrawRoom(corridor, CORRIDOR);
  }
}

void Game::DrawRoom(const Room &room, RoomType type) {
  for (int i = 0; i < abs(room.width); ++i) {
    for (int j = 0; j < abs(room.height); ++j) {
      sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
      tileShape.setPosition(sf::Vector2f((room.x + i) * TILE_SIZE, (room.y + j) * TILE_SIZE));

      switch (type) {
        case ROOM:tileShape.setTexture(room.tileTextures[i][j]);
          break;
        case CORRIDOR:tileShape.setTexture(&corridor_t1);
          break;
      }

      window_.draw(tileShape);
    }
  }
}

