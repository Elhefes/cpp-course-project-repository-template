//
// Created by dannypa on 13.11.23.
//

#ifndef DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
#define DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
#include <unordered_set>
#include "Creature.hpp"
#include "../room.hpp"
#include "../helper.hpp"

// Constants
// monster behavior
const int TICKS_PER_SECOND = 2;
const long TICK_TIME = CLOCKS_PER_SEC / TICKS_PER_SECOND;
const float MONSTER_ATTACK_RADIUS = 2.f;
const float MONSTER_DIRECTION_CHANGE_PROBABILITY = 0.2f;
// player behavior
const float PLAYER_ATTACK_RADIUS = 2.2f;
// spawn monsters
const int DEFAULT_MONSTER_DAMAGE = 10;
const int DEFAULT_MONSTER_HEALTH = 60;
const float DEFAULT_MONSTER_VELOCITY = 0.085f;

const float BOSS_MONSTER_DAMAGE_MULTIPLIER = 1.5f;
const float BOSS_MONSTER_DAMAGE = DEFAULT_MONSTER_DAMAGE * BOSS_MONSTER_DAMAGE_MULTIPLIER;
const int BOSS_MONSTER_HEALTH = 250;
const float BOSS_MONSTER_VELOCITY = 0.07f;
// spawn items
const float POTION_SPAWN_PROBABILITY = 0.33f;

class Player;

/// @brief Class for enemies
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

  /// @brief Updates the monster speed every fixed amount of seconds; monsters usually try to approach the player
  /// but can go other direction with small chance.
  /// @param p the player to approach
  void tick(Player &p);

 private:
  /// @brief The moment the last tick was made
  long lastTick_ = 0;
};

/// @brief Class for the Player
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

  /// @return current room index
  int GetRoomIndex() const;

  /// @return current position
  sf::Vector2f GetPosition();

  /// @brief Sets the room
  /// @param room new room
  void SetRoom(Room &room) override;;

  /// @brief Sets the room, if needed spawns the monster and the potions
  /// @param room new room
  /// @param monsters vector of pointers to monsters
  /// @param potionPos vector of positions of health potions
  void SetRoom(Room &room, std::vector<Monster *> &monsters, std::vector<sf::Vector2f> &potionPos);

  /// @brief Updates the player; if needed spawns the monsters and potions
  /// @param monsters vector of pointers to monsters
  /// @param potions vector of positions of health potions
  void Update(std::vector<Monster *> &monsters, std::vector<sf::Vector2f> potions);

  /// @brief Sets rooms
  /// @param rooms new vector of rooms
  void SetRooms(const std::vector<Room> &rooms);

  /// @brief Set monstersCleared param
  /// @param monstersCleared new value for the param
  void SetMonstersCleared(bool monstersCleared);

  /// @brief Sets itemInUse
  /// @param index new value for itemInUse
  void SetItemInUse(int index);

  /// @return item in use index
  int GetItemInUse() const;

  /// @brief Tries to heal the player; if the current item in use is not a health potion or there are no health potions
  /// left does nothing; otherwise heals the player by the amount specified by the potion.
  void TryHealing();

  /// @brief Tries to attack; if there are no monsters close enough, does nothing; otherwise attacks the closest one
  /// @param monsters vector of pointers to monsters
  void TryAttack(const std::vector<Monster *> &monsters);

  /// @brief Tries to pick up a potion; if there are no potions close enough, does nothing; otherwise picks up the
  /// closest one
  /// @param potionPositions vector of positions of health potions
  void TryPickup(std::vector<sf::Vector2f> &potionPositions);

  /// @brief Spawns the monsters in the room with the player. If the room is a corridor does nothing.
  /// @param res vector of pointers to monsters to add the spawned monsters to.
  void SpawnMonsters(std::vector<Monster *> &res);

  /// @brief Spawns potions in the room with the player with predefined probability.
  /// @param pos vector of positions of health potions to add the spawned potions to.
  void SpawnPotion(std::vector<sf::Vector2f> &pos);

 private:
  /// @brief Index of the item from the inventory that is currently in use.
  int itemInUse = 0;

  /// @brief Vector of all the rooms in order they are supposed to be visited.
  std::vector<Room> rooms_;

  /// @brief Current room index
  int roomIndex_;

  /// @brief Boolean value. If the monsters in the room are cleared equals true; equals false otherwise.
  bool monstersCleared_;

  /// @brief Gets available rooms for player to go to; by default, the current room is available;
  /// if monstersCleared_ = true, then the next room is also available.
  /// @return vector of available rooms
  std::vector<Room> GetAvailableRooms() override;

  /// @brief Gets the direction the player is facing; the direction is calculated as a vector from the player to
  /// the cursor position.
  /// @return vector specifying the direction the player is facing.
  sf::Vector2f GetFacingDirection() override;

  /// @brief Updates room index based on the current room and vector of rooms.
  void UpdateRoomIndex();
};

#endif //DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
