//
// Created by dannypa on 05.11.23.
//

#ifndef DUNGEONCRAWLER_CHARACTER_H
#define DUNGEONCRAWLER_CHARACTER_H

#include <algorithm>
#include <string>
#include <iostream>
#include "../Item.hpp" // maybe change path later idk where it would end up
#include "SFML/Graphics.hpp"

/// @brief Base class for every "alive" entity in the dungeon
class Creature {
 public:

  Creature(const std::string &type, const std::string &name, int maxHealth,
           const sf::Vector2<float> &initialPos,
           sf::RenderWindow &window,
           std::ostream &logger = std::cout,
           const sf::CircleShape &sprite = sf::CircleShape(50),
           const std::vector<Item> &inventory = {});

  /// @brief Checks if the creature is alive.
  /// @return true if the creature is alive, false otherwise
  [[nodiscard]] bool IsAlive() const { return health_ > 0; }

  /// @return description_
  [[nodiscard]] const std::string &GetDescription() const;

  /// @brief Handles the logic when this creature is attacked.
  /// @param base_damage Base attack damage (actual damage may be later recalculated somehow)
  /// @param c2 the creature who attacks
  /// @return the damage taken
  int TakeHit(int base_damage, const Creature &c2);

  /// @brief Updates state of the creature.
  /// Later probably need to pass something cleverer, like game class, tho i am not sure yet.
  void Update();

  /// @brief Draws the creature's sprite in a given window.
  /// @param window window to draw the creature.
  void Draw() const;

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

  /// @return inventory
  const std::vector<Item> &GetInventory() const;
  /// @return position
  const sf::Vector2<float> &GetPosition() const;
  /// @return velocity
  const sf::Vector2<float> &GetVelocity() const;

 protected:
  /// @brief max movement speed of the creature\nNote: this is the limit for vx and vy separately.
  float max_velocity_;
  /// @brief max health of the creature
  int maxHealth_;
  /// @brief current health of the creature.
  /// Note: could be made unsigned int, but I am afraid that at some point I will forget that it is an unsigned
  /// int and write something like health = max(health - damage, 0) and give some creature 2**32 hp.
  int health_;
  /// @brief type of the character (e.g. monster)
  std::string type_;
  /// @brief name of the character
  std::string name_;
  /// @brief description in the format "Creature of type <type_> named <name>"
  std::string description_;
  /// @brief vector of items a creature currently has. Don't see the need to store references for now.
  std::vector<Item> inventory_;
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

  /// @brief Reduces health by damage. If damage is greater then health, sets health to 0.
  /// @param damage amount to reduce health_ by
  void TakeDamage_(int damage) { health_ = std::max(0, health_ - damage); }
};

#endif //DUNGEONCRAWLER_CHARACTER_H
