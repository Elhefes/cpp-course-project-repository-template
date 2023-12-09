//
// Created by dannypa on 13.11.23.
//

#ifndef DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
#define DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
#include <unordered_set>
#include "Creature.hpp"
#include "../room.hpp"
#include "../helper.hpp"

const long TICK_TIME = CLOCKS_PER_SEC / 2;

class Player;
// MONSTER
const float ATTACK_RADIUS = 2.f;
class Monster : public Creature {
 public:
  Monster(const std::string &type,
          const std::string &name,
          int max_health,
          float max_velocity,
          const sf::Vector2<float> &initial_pos,
          sf::RenderWindow &window,
          const Room &room,
          int base_damage,
          sf::Texture &texture,
          std::ostream &logger = std::cout,
          Inventory inventory = Inventory()) : Creature(type,
                                                        name,
                                                        max_health,
                                                        max_velocity,
                                                        initial_pos,
                                                        window,
                                                        room, base_damage, texture,
                                                        logger,
                                                        inventory) {}

  void tick(Player &p);

 private:
  long lastTick_ = 0;
};

// PLAYER
class Player : public Creature {
 public:
  Player(const std::string &type, const std::string &name, int maxHealth, float maxVelocity,
         const sf::Vector2<float> &initialPos,
         sf::RenderWindow &window,
         Room room,
         sf::Texture &texture,
         std::ostream &logger = std::cout,
         Inventory inventory = Inventory()) :
      Creature(type, name, maxHealth, maxVelocity, initialPos, window, room, 25, texture, logger, inventory) {};

  int GetRoomIndex();

  sf::Vector2f GetPosition();

  void SetRoom(Room &room) override;;

  void SetRoom(Room &room, std::vector<Monster *> &monsters, std::vector<sf::Vector2f> &potionPos);

  void Update(std::vector<Monster *> &monsters, std::vector<sf::Vector2f> potions);

  void SetRooms(const std::vector<Room> &rooms);

  void SetMonstersCleared(bool monstersCleared);

  void SetItemInUse(int index);

  int GetItemInUse() const;

  void tryHealing();

  void TryAttack(const std::vector<Monster *> &monsters);

  void TryPickup(std::vector<sf::Vector2f> &potionPositions);

  void SpawnMonsters(sf::RenderWindow &window, std::vector<Monster *> &res);

  void SpawnPotion(std::vector<sf::Vector2f> &pos);

 private:
  int itemInUse = 0;
  std::vector<Room> rooms_;
  int roomIndex_;
  bool monstersCleared_;

  std::vector<Room> GetAvailableRooms() override;

  sf::Vector2f GetFacingDirection() override;

  void UpdateRoomIndex();
};

#endif //DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
