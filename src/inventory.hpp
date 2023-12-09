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
 * @brief Class defining an inventory_ to manage items.\n
 * All the items are stored in a vector; each item is either sword or a health potion. The item in use is highlighted
 * while drawing the inventory. Additionally there are two vectors swords_ and potions_ which store swords and potions
 * separately (this is done to return the object of type sword/potion)
 */
class Inventory {
 private:
  /// @brief Map storing the number of the items of the given name
  std::unordered_map<std::string, int> counter_;

  /// @brief Vector containing a pair of boolean value showing if the item on the i-th position in the inventory
  /// is a sword and index of the i-th item in the corresponding vector (swords_ or potions_)
  std::vector<std::pair<bool, int>> isSword_;

  /// @brief vector of all the swords
  std::vector<Sword> swords_;

  /// @brief vector of all the potions
  std::vector<HealthPotion> potions_;

  /// @brief Adds an item to the inventory.
  /// @tparam T type of the item (currently HealthPotion or Sword)
  /// @param item the item to add
  /// @param itemsVector vector of the items of the corresponding type
  /// @param quantity number of the items to add
  template<typename T>
  void AddItem(const T &item, std::vector<T> &itemsVector, int quantity);

  /// @brief Draws the given items
  /// @tparam T type of the items
  /// @param items vector of the items to draw
  /// @param t texture for every item
  /// @param x x coordinate for the first item
  /// @param y y coordinate for the items
  /// @param window window to draw the items in
  /// @param itemInUse index of the item that is currently in use to highlight
  /// @return the x coordinate at which the next item can be drawn
  template<typename T>
  float DrawItems(std::vector<T> items,
                  const sf::Texture &t,
                  float x,
                  float y,
                  sf::RenderWindow &window,
                  bool itemInUse);

 public:

  /// @brief Adds a sword to the inventory
  /// @param item sword to add
  /// @param quantity the number of swords to add
  void AddSword(const Sword &item, int quantity) {
    AddItem(item, swords_, quantity);
  }

  /// @brief Adds a potion to the inventory
  /// @param item potion to add
  /// @param quantity the number of potions to add
  void AddPotion(const HealthPotion &item, int quantity) {
    AddItem(item, potions_, quantity);
  }

  /**
   * @brief Get the current size of the inventory_.
   * @return The size of the inventory_.
   */
  int GetSize();

  /// @brief Draws the inventory
  /// @param window window to draw the inventory in
  /// @param itemInUse item that is currently in use (for highlighting)
  void Draw(sf::RenderWindow &window, int itemInUse);

  /// @param index position of the sword
  /// @return The sword in the given position.
  Sword GetSword(int index);

  /// @param index position of the potion
  /// @return The potion in the given position.
  HealthPotion GetPotion(int index);

  /// @param index position of the potion
  /// @return The healing from the potion in the given position.
  int GetHealingAmount(int index);

  /// @param i the position to check
  /// @return True if the item in the position i is a sword; false otherwise.
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
