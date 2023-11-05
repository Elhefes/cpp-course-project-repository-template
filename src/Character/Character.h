//
// Created by dannypa on 05.11.23.
//

#ifndef DUNGEONCRAWLER_CHARACTER_H
#define DUNGEONCRAWLER_CHARACTER_H

/**
 * Base class for every "alive" entity in the dungeon
 */
class Character {
 public:

  /// @brief Checks if the creature is alive.
  /// @return true if the creature is alive, false otherwise
  [[nodiscard]] bool IsAlive() const { return health_ > 0; }

  void TakeDamage(int damage) {}

 protected:
  /// @brief current health of the creature.
  /// Note: could be made unsigned int, but I am afraid that at some point I will forget that it is an unsigned
  /// int and write something like health = max(health - damage, 0) and give some creature 2**32 hp.
  int health_;
};

#endif //DUNGEONCRAWLER_CHARACTER_H
