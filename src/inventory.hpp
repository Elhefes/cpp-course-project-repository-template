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
 * @brief Class defining an inventory to manage items.
 */
class Inventory {
 private:
//  std::vector<Item> items; ///< Vector to hold items in the inventory.
  std::unordered_map<std::string, int> counter;
  std::vector<std::pair<bool, int>> isSword_;
  std::vector<Sword> swords;
  std::vector<HealthPotion> potions;

  template<typename T>
  void AddItem_(const T &item, std::vector<T> &itemsVector, int quantity) {
    if (counter.find(item.GetName()) == counter.end()) {
      counter[item.GetName()] = 0;
      isSword_.emplace_back(item.IsSword(), itemsVector.size());
      itemsVector.push_back(item);
    }
    counter[item.GetName()] += quantity;
  }

 public:
  /**
   * @brief Add an item to the inventory.
   * @param item The item to add.
   * @param quantity The amout of the item to add
   */
//  template<typename T>
//  // it is what it is. i literally do not know a better way then template functions.
//  void addItem(const T &item, int quantity) {
//    if (counter.find(item.GetName()) == counter.end()) {
//      counter[item.GetName()] = 0;
//      if (item.IsSword()) {
//        isSword_.emplace_back(true, swords.size());
//        swords.push_back(item);
//      } else {
//        isSword_.emplace_back(false, potions.size());
//        potions.push_back(item);
//      }
//    }
//    counter[item.GetName()] += quantity;
//  }
  void addSword(const Sword &item, int quantity) {
    AddItem_(item, swords, quantity);
  }

  void addPotion(const HealthPotion &item, int quantity) {
    AddItem_(item, potions, quantity);
  }

  /**
   * @brief Remove a specified quantity of an item from the inventory.
   * @param itemName The name of the item to remove.
   * @param quantity The quantity of the item to be removed.
   * @return True if the specified quantity of the item was successfully removed, false otherwise.
   */
//  bool removeItem(const std::string &itemName, int quantity) {
//    if (items.find(itemName) == items.end() || items[itemName].second < quantity) {
//      return false;
//    }
//    items[itemName].second -= quantity;
//    if (items[itemName].second == 0) {
//      items.erase(itemName);
//    }
//    return true;
//  }


  /**
   * @brief Check if an item is present in the inventory.
   * @param item The item to check.
   * @return True if the item is found, otherwise false.
   */
  /*
  bool hasItem(const std::string& itemName) {
  return std::find_if(items.begin(), items.end(),
      [&itemName](const auto& item) { return std::get<0>(item) == itemName; }
  ) != items.end();
  }*/


  /**
   * @brief Get the count of a specific item in the inventory.
   * @param item The item to count.
   * @return The count of the item in the inventory.
   */
  int getItemCount(const std::string &itemName) {
    return counter[itemName];
  }

  /**
   * @brief Display the inventory contents.
   */
//  void displayInventory() { todo: do this
//    std::cout << "Inventory:\n";
//    for (const auto &item : items) {
//      std::cout << item.first << " - Quantity: " << item.second.second << "\n";
//    }
//  }

  /**
   * @brief Get the current size of the inventory.
   * @return The size of the inventory.
   */
  int getSize() {
    return swords.size() + potions.size();
  }

  /**
   * @brief Clear all items from the inventory.
   */
//  void clearInventory() { todo: maybe do this..?
//    items.clear();
//  }

  void Draw(sf::RenderWindow &window) const { // todo: highlight the item in use
    sf::Vector2f center = window.getView().getCenter();
    float x = center.x - window.getView().getSize().x / 2 + 0.5;
    float y = center.y - window.getView().getSize().y / 2 + 0.5;
    for (const auto &item : swords) {
      sf::RectangleShape rect(sf::Vector2f(1.f, 1.f));
      rect.setTexture(&sword_inv_t);
      rect.setPosition(sf::Vector2f(x, y));
      window.draw(rect);
      x += 1.3f;
    }
    // assumes that there is only one health potion for now i guess as all the textures are same
    for (const auto &item : potions) {
      sf::RectangleShape rect(sf::Vector2f(1.f, 1.f));
      rect.setTexture(&potion_inv_t);
      rect.setPosition(sf::Vector2f(x, y));
      window.draw(rect);
      x += 1.3f;
    }
  }

  Sword GetSword(int index) {
    // assumes that isSword_[index] is true
    // this dumb implementation assumes that player do not drop swords
    return swords[isSword_[index].second];
  }

  HealthPotion GetPotion(int index) {
    return potions[isSword_[index].second];
  }

  int GetHealingAmount(int index) {
    if (isSword_[index].second) return 0;
    HealthPotion potion = GetPotion(index);
    if (counter[potion.GetName()] > 0) {
      counter[potion.GetName()] -= 1;
      return potion.GetHpRestored();
    } else {
      return 0;
    }
  }

  bool IsSword(int i) { return isSword_[i].first; }
};

#endif // INVENTORY_HPP
