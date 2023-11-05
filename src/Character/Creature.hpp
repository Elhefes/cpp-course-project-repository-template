//
// Created by dannypa on 05.11.23.
//

#ifndef DUNGEONCRAWLER_CHARACTER_H
#define DUNGEONCRAWLER_CHARACTER_H

#include <algorithm>
#include <string>

///
/// Base class for every "alive" entity in the dungeon
///
class Creature {
 public:

  /// @brief Checks if the creature is alive.
  /// @return true if the creature is alive, false otherwise
  [[nodiscard]] bool IsAlive() const { return health_ > 0; }

  /// @brief Reduces health by damage
  /// @param damage amount to reduce health_ by
  void TakeDamage(int damage) { health_ = std::max(0, health_ - damage); }

  const std::string &GetDescription() const;

  int TakeHit(int base_damage, const Creature &c2);

 protected:
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
};

#endif //DUNGEONCRAWLER_CHARACTER_H
