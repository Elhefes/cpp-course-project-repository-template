#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Item.hpp"

/**
 * @brief Class defining an inventory to manage items.
 */
class Inventory {
 private:
  std::unordered_map<std::string, std::pair<Item, int>> items; ///< Vector to hold items in the inventory.
  std::vector<std::pair<Item, int>> getItemsVector_() const {
    std::vector<std::pair<Item, int>> values;
    for (const auto &item : items) values.push_back(item.second);
    std::sort(values.begin(), values.end(), [](const auto &a, const auto &b) {
      if (a.first.IsSword() == b.first.IsSword()) return a.first.GetName() < b.first.GetName();
      return a.first.IsSword();
    });
    return values;
  }; // incredibly inefficient, however, maybe we do not care when
  // the inventory is as small

 public:
  /**
   * @brief Add an item to the inventory.
   * @param item The item to add.
   * @param quantity The amout of the item to add
   */
  void addItem(const Item &item, int quantity) {
    if (items.find(item.GetName()) == items.end()) {
      items[item.GetName()] = {item, 0};
    }
    items[item.GetName()].second += quantity;
  }

  /**
   * @brief Remove a specified quantity of an item from the inventory.
   * @param itemName The name of the item to remove.
   * @param quantity The quantity of the item to be removed.
   * @return True if the specified quantity of the item was successfully removed, false otherwise.
   */
  bool removeItem(const std::string &itemName, int quantity) {
    if (items.find(itemName) == items.end() || items[itemName].second < quantity) {
      return false;
    }
    items[itemName].second -= quantity;
    if (items[itemName].second == 0) {
      items.erase(itemName);
    }
    return true;
  }


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
    return items[itemName].second;
  }

  /**
   * @brief Display the inventory contents.
   */
  void displayInventory() {
    std::cout << "Inventory:\n";
    for (const auto &item : items) {
      std::cout << item.first << " - Quantity: " << item.second.second << "\n";
    }
  }

  /**
   * @brief Get the current size of the inventory.
   * @return The size of the inventory.
   */
  int getSize() {
    return items.size();
  }

  /**
   * @brief Clear all items from the inventory.
   */
  void clearInventory() {
    items.clear();
  }

  void Draw(sf::RenderWindow &window) const {
    sf::Vector2f center = window.getView().getCenter();
    float x = center.x - window.getView().getSize().x / 2 + 0.5;
    float y = center.y - window.getView().getSize().y / 2 + 0.5;
    auto values = getItemsVector_();
    for (const auto &item : values) {
      if (item.first.IsSword()) {
        sf::RectangleShape rect(sf::Vector2f(1.f, 1.f));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(0.1f);
        rect.setOutlineColor(sf::Color::Red);
        rect.setPosition(sf::Vector2f(x, y));
        window.draw(rect);
      } else {
        sf::CircleShape circle(0.5f);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(0.1f);
        circle.setOutlineColor(sf::Color::Blue);
        circle.setPosition(sf::Vector2f(x, y));
        window.draw(circle);
      }
      x += 1.3f;
    }
  }

  Item GetByIndex(int index) {
    return getItemsVector_()[index].first; // if it crashes, it crashes.
  }
};

#endif // INVENTORY_HPP
