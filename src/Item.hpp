#ifndef DUNGEONCRAWLER_SRC_ITEM_HPP_
#define DUNGEONCRAWLER_SRC_ITEM_HPP_

#include <iostream>
#include "string"

class Item {
 public:
  Item() = default;
  Item(const std::string &name, bool isSword) : name_(name), isSword_(isSword) {};

  [[nodiscard]] const std::string &GetName() const { return name_; }

  [[nodiscard]] bool IsSword() const { return isSword_; }

  static void Draw(sf::RenderWindow &window,
                   const sf::Vector2f &pos,
                   float maxSize,
                   const sf::Texture &t) {
    // todo: if i had more time, i would rewrite the item to have texture as a field
    //  and the method would not have been static
    sf::Sprite sprite(t);
    sf::FloatRect itemBounds = sprite.getGlobalBounds();
    float scale = maxSize / std::max(itemBounds.width, itemBounds.height);
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(pos);
    window.draw(sprite);
  }
 protected:
  std::string name_;
  bool isSword_{};
};

class Sword : public Item {
 public:
  Sword() = default;
  Sword(const std::string &name, float multiplier) : Item(name, true), multiplier_(multiplier) {};

  [[nodiscard]] float GetMultiplier() const { return multiplier_; }
 private:
  float multiplier_;
};

class HealthPotion : public Item {
 public:
  HealthPotion() = default;
  explicit HealthPotion(float hpRestored) : Item("Health potion " + std::to_string(hpRestored), false),
                                            hpRestored_(hpRestored) {};

  [[nodiscard]] float GetHpRestored() const { return hpRestored_; };
 private:
  float hpRestored_{};
};
#endif //DUNGEONCRAWLER_SRC_ITEM_HPP_