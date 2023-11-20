//
// Created by dannypa on 13.11.23.
//

#ifndef DUNGEONCRAWLER_SRC_CREATURE_ASSASSIN_HPP_
#define DUNGEONCRAWLER_SRC_CREATURE_ASSASSIN_HPP_
#include "Player.hpp"

const int MAX_HEALTH = 50;
class Assassin : public Player { ;
 public:
  /// @brief assasin teleports to random location
  void Special() override;
  Assassin(const std::string &name,
           const sf::Vector2<float> &initialPos,
           sf::RenderWindow &window,
           std::ostream &logger = std::cout,
           const sf::CircleShape &sprite = sf::CircleShape(50),
           const std::vector<Item> &inventory = {}) :
      Player("Assassin", name, MAX_HEALTH, initialPos, window, logger, sprite, inventory) {}
};

#endif //DUNGEONCRAWLER_SRC_CREATURE_ASSASSIN_HPP_
