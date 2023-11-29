//
// Created by dannypa on 13.11.23.
//

#ifndef DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
#define DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
#include "Creature.hpp"
#include "../room.hpp"
#include "../helper.hpp"

const int CAMERA_WIDTH = 800u; // TODO: change later to width constants
const int CAMERA_HEIGHT = 600u;
const double TICK_TIME = CLOCKS_PER_SEC / 100.0;

class Monster;
// PLAYER
class Player : public Creature {
 public:
  Player(const std::string &type, const std::string &name, int maxHealth, float maxVelocity,
         const sf::Vector2<float> &initialPos,
         sf::RenderWindow &window,
         Room room,
         std::vector<Room> rooms_ = {},
         std::vector<Room> corridors_ = {},
         std::ostream &logger = std::cout,
         const sf::CircleShape &sprite = sf::CircleShape(0.1f),
         const std::vector<Item> &inventory = {}) :
      Creature(type, name, maxHealth, maxVelocity, initialPos, window, room, 25, logger, sprite, inventory) {};

  /// @brief Special ability of each player class
  void Special() {};
  void SetPosition(const sf::Vector2<float> &position) override {
    position_ = position;
  }
  void UpdateRooms(std::vector<Room> rooms) {
    rooms_ = rooms;
  }
  void UpdateCorridors(std::vector<Room> corridors) {
    corridors_ = corridors;
  }
  sf::Vector2f getPosition() {
    return position_;
  }
  void SetRoom(Room &room, std::vector<Monster *> &monsters);
};
//void Player::SetRoom(Room &room) {
//  // player changes the room; need to spawn those juicy enemies
//  room_ = room;
//}

// MONSTER
const float ATTACK_RADIUS = 0.5f;
class Monster : public Creature {
 public:
  Monster(const std::string &type,
          const std::string &name,
          int max_health,
          float max_velocity,
          const sf::Vector2<float> &initial_pos,
          sf::RenderWindow &window,
          const Room &room,
          std::ostream &logger = std::cout,
          const sf::CircleShape &sprite = sf::CircleShape(0.3f),
          const std::vector<Item> &inventory = {}) : Creature(type,
                                                              name,
                                                              max_health,
                                                              max_velocity,
                                                              initial_pos,
                                                              window,
                                                              room, 0,
                                                              logger,
                                                              sprite,
                                                              inventory) { base_damage_ = 10; } // todo: add to constructor

  static void SpawnMonsters(Room &room, sf::RenderWindow &window, std::vector<Monster *> &res);
  void tick(Player &p);
 private:
  long lastTick_ = 0;
};

#endif //DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
