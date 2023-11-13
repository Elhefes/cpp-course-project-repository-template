//
// Created by dannypa on 13.11.23.
//

#ifndef DUNGEONCRAWLER_SRC_CREATURE_PLAYER_HPP_
#define DUNGEONCRAWLER_SRC_CREATURE_PLAYER_HPP_
#include "Creature.hpp"

class Player : public Creature {
 public:
  Player(const std::string &type, const std::string &name, int maxHealth,
         const sf::Vector2<float> &initialPos,
         sf::RenderWindow &window,
         std::ostream &logger = std::cout,
         const sf::CircleShape &sprite = sf::CircleShape(50),
         const std::vector<Item> &inventory = {}) :
      Creature(type, name, maxHealth, initialPos, window, logger, sprite, inventory) {};

  /// @brief Special ability of each player class
  virtual void Special() = 0;
};

#endif //DUNGEONCRAWLER_SRC_CREATURE_PLAYER_HPP_
