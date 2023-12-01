//
// Created by dannypa on 05.11.23.
//

#ifndef DUNGEONCRAWLER_CHARACTER_H
#define DUNGEONCRAWLER_CHARACTER_H

#include <algorithm>
#include <string>
#include <iostream>
#include "../inventory.hpp" // maybe change path later idk where it would end up
#include "SFML/Graphics.hpp"
#include "../helper.hpp"
#include "../room.hpp"
#include "../textureManager.hpp"

/// @brief Base class for every "alive" entity in the dungeon
class Creature {
 public:
  Creature(const std::string &type,
           const std::string &name,
           int maxHealth,
           float maxVelocity,
           const sf::Vector2<float> &initialPos,
           sf::RenderWindow &window,
           const Room &room,
           int base_damage,
           std::ostream &logger = std::cout,
           const sf::CircleShape &sprite = sf::CircleShape(50),
           Inventory inventory = Inventory(),
           std::vector<Room> rooms = {},
           std::vector<Room> corridors = {});

  /// @brief Checks if the creature is alive.
  /// @return true if the creature is alive, false otherwise
  [[nodiscard]] bool IsAlive() const { return health_ > 0; }

  /// @return description_
  [[nodiscard]] const std::string &GetDescription() const;
  [[nodiscard]] const std::string &GetType() const;

  /// @brief Handles the logic when this creature is attacked.
  /// @param base_damage Base attack damage (actual damage may be later recalculated somehow)
  /// @param c2 the creature who attacks
  /// @return the damage taken
  int TakeHit(int base_damage, const Creature &c2);

  int Attack(Creature &c2, const Item *item = nullptr);

  /// @brief Updates state of the creature.
  /// Later probably need to pass something cleverer, like game class, tho i am not sure yet.
  void Update(bool monstersKilled);

  bool isInsideAnyRoom(float x, float y);

  /// @brief Draws the creature's sprite in a given window.
  /// @param camera current camera state
  void Draw();

  /// @brief Setter for velocity.
  /// @param newVelocity
  void SetVelocity(const sf::Vector2<float> &newVelocity);
  /// @brief Sets x velocity.
  /// @param nvx new x velocity.
  void SetVelocityX(float nvx);
  /// @brief Sets y velocity.
  /// @param nvy new y velocity.
  void SetVelocityY(float nvy);
  void SetHealth(int health);
  void SetSprite(const sf::CircleShape &sprite);
  virtual void SetPosition(const sf::Vector2<float> &position);
  virtual void SetRoom(Room &room);

  /// @return inventory
  const Inventory &GetInventory() const;
  /// @return position
  const sf::Vector2<float> &GetPosition() const;
  /// @return max velocity
  const float GetMaxVelocity() const;
  /// @return velocity
  const sf::Vector2<float> &GetVelocity() const;
  /// @return current room
  const Room &GetRoom() const;
  /// @return inventory of the creture
  Inventory &GetInventory();

 protected:
  /// @brief max movement speed of the creature\nNote: this is the limit for vx and vy separately.
  const float maxVelocity_;
  /// @brief max health of the creature
  const int maxHealth_;
  /// @brief current health of the creature.
  /// Note: could be made unsigned int, but I am afraid that at some point I will forget that it is an unsigned
  /// int and write something like health = max(health - damage, 0) and give some creature 2**32 hp.
  int health_;
  /// @brief damage that creature deals with no items
  int base_damage_;
  /// @brief type of the character (e.g. monster)
  const std::string type_;
  /// @brief name of the character
  std::string name_;
  /// @brief description in the format "Creature of type <type_> named <name>"
  std::string description_;
  /// @brief the inventory of the creature
  Inventory inventory_;
  /// @brief change to actual sprite later
  sf::CircleShape sprite_;
  /// @brief position of the creature on the screen
  sf::Vector2<float> position_;
  /// @brief current velocity of the creature
  sf::Vector2<float> velocity_;
  /// @brief window in which the creature is supposed to be drawn
  sf::RenderWindow &window_;
  /// @brief stream to log information about the class
  std::ostream &logger_;
  /// @brief room the creature is in
  
  sf::RectangleShape creatureRect;
  Room room_;
  std::vector<Room> rooms_;
  std::vector<Room> corridors_;

  /// @brief Reduces health by damage. If damage is greater then health, sets health to 0.
  /// @param damage amount to reduce health_ by
  void TakeDamage_(int damage) { health_ = std::max(0, health_ - damage); }
};

#endif //DUNGEONCRAWLER_CHARACTER_H
