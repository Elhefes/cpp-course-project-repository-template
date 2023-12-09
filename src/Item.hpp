#ifndef DUNGEONCRAWLER_SRC_ITEM_HPP_
#define DUNGEONCRAWLER_SRC_ITEM_HPP_

#include <iostream>
#include "string"
#include <SFML/Graphics.hpp>

/// @brief Basic class for items in the inventory.
class Item {
 public:
  Item() = default;
  Item(const std::string &name, bool isSword) : name_(name), isSword_(isSword) {};

  [[nodiscard]] const std::string &GetName() const { return name_; }

  [[nodiscard]] bool IsSword() const { return isSword_; }

  /// @brief Draws the item.
  /// @param window Window to draw the item in.
  /// @param pos Position to draw the item at.
  /// @param maxSize Maximum of allowed width and height.
  /// @param t Texture to use.
  static void Draw(sf::RenderWindow &window,
                   const sf::Vector2f &pos,
                   float maxSize,
                   const sf::Texture &t);
 protected:
  /// @brief name of the item.
  std::string name_;

  /// @brief true if the item is a sword, false otherwise.
  bool isSword_{};
};

/// @brief A sword - an item that buffs the damage (multiplies it by some value)
class Sword : public Item {
 public:
  Sword() = default;
  Sword(const std::string &name, float multiplier) : Item(name, true), multiplier_(multiplier) {};

  [[nodiscard]] float GetMultiplier() const { return multiplier_; }
 private:
  /// @brief value to multiply damage by
  float multiplier_ = 1;
};

/// @brief A health potion - an item that heals the player by the given amount
class HealthPotion : public Item {
 public:
  HealthPotion() = default;
  explicit HealthPotion(float hpRestored) : Item("Health potion " + std::to_string(hpRestored), false),
                                            hpRestored_(hpRestored) {};

  [[nodiscard]] float GetHpRestored() const { return hpRestored_; };
 private:
  /// @brief Amount to heal by.
  float hpRestored_ = 10;
};
#endif //DUNGEONCRAWLER_SRC_ITEM_HPP_