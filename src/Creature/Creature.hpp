//
// Created by dannypa on 05.11.23.
//

#ifndef DUNGEONCRAWLER_CHARACTER_H
#define DUNGEONCRAWLER_CHARACTER_H

#include <algorithm>
#include <string>
#include "../Item.hpp" // maybe change path later idk where it would end up
#include "SFML/Graphics.hpp"

///
/// Base class for every "alive" entity in the dungeon
///
class Creature {
 public:

  Creature(const std::string &type, const std::string &name, int maxHealth, const sf::Vector2<float> &initialPos,
           const sf::CircleShape &sprite = sf::CircleShape(50));

  /// @brief Checks if the creature is alive.
  /// @return true if the creature is alive, false otherwise
  [[nodiscard]] bool IsAlive() const { return health_ > 0; }

  /// @brief Reduces health by damage.
  /// @param damage amount to reduce health_ by
  void TakeDamage(int damage) { health_ = std::max(0, health_ - damage); }

  /// @return description_
  [[nodiscard]] const std::string &GetDescription() const;

  /// @brief Handles the logic when this creature is attacked.
  /// @param base_damage Base attack damage (actual damage may be later recalculated somehow)
  /// @param c2 the creature who attacks
  /// @return the damage taken
  int TakeHit(int base_damage, const Creature &c2);

  /// @brief Updates state of the creature.
  /// @param window Window which the creature is currently in. Passed to check that it is not leaving the window. \n
  /// Later probably need to pass something cleverer, like game class, tho i am not sure yet.
  void Update(const sf::RenderWindow &window);

  /// @brief Draws the creature's sprite in a given window.
  /// @param window window to draw the creature.
  void Draw(sf::RenderWindow &window) const;

  /// @brief Setter for velocity.
  /// @param newVelocity
  void SetVelocity(const sf::Vector2<float> &newVelocity) { velocity_ = newVelocity; };
  /// @brief Sets x velocity.
  /// @param nvx new x velocity.
  void SetVelocityX(float nvx) { velocity_.x = nvx; };
  /// @brief Sets y velocity.
  /// @param nvy new y velocity.
  void SetVelocityY(float nvy) { velocity_.y = nvy; };

 protected:
  /// @brief max movement speed of the creature
  float movement_speed_;
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
  std::vector<Item> items_;
  /// @brief change to actual sprite later
  sf::CircleShape sprite_;
  /// @brief position of the creature on the screen
  sf::Vector2<float> position_;
  /// @brief current velocity of the creature
  sf::Vector2<float> velocity_;
};

#endif //DUNGEONCRAWLER_CHARACTER_H
