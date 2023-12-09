#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Item.hpp"
#include "textureManager.hpp"

/**
 * @brief Class defining an inventory_ to manage items.
 */
class Inventory {
 private:
  std::unordered_map<std::string, int> counter_;
  std::vector<std::pair<bool, int>> isSword_;
  std::vector<Sword> swords_;
  std::vector<HealthPotion> potions_;

  template<typename T>
  void AddItem(const T &item, std::vector<T> &itemsVector, int quantity);

  template<typename T>
  float DrawItems(std::vector<T> items,
                  const sf::Texture &t,
                  float x,
                  float y,
                  sf::RenderWindow &window,
                  bool itemInUse);

 public:

  void AddSword(const Sword &item, int quantity) {
    AddItem(item, swords_, quantity);
  }

  void AddPotion(const HealthPotion &item, int quantity) {
    AddItem(item, potions_, quantity);
  }

  /**
   * @brief Get the current size of the inventory_.
   * @return The size of the inventory_.
   */
  int GetSize();

  void Draw(sf::RenderWindow &window, int itemInUse);

  Sword GetSword(int index);

  HealthPotion GetPotion(int index);

  int GetHealingAmount(int index);

  bool IsSword(int i) { return isSword_[i].first; }
};

template<typename T>
void Inventory::AddItem(const T &item, std::vector<T> &itemsVector, int quantity) {
  if (counter_.find(item.GetName()) == counter_.end()) {
    counter_[item.GetName()] = 0;
    isSword_.emplace_back(item.IsSword(), itemsVector.size());
    itemsVector.push_back(item);
  }
  counter_[item.GetName()] += quantity;
}
#endif // INVENTORY_HPP
