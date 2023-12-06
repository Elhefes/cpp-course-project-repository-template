#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "Item.hpp"
#include <SFML/Graphics.hpp>
#include "textureManager.hpp"

/**
 * @brief Class defining an inventory to manage items.
 */
class Inventory {
private:
    std::vector<std::tuple<std::string, int, sf::Texture>> items; ///< Vector to hold items in the inventory.

public:
    /**
     * @brief Add an item to the inventory.
     * @param item The item to add.
     * @param quantity The amout of the item to add
     * @param quantity The texture of the item
     */
    void addItem(const std::string& itemName, int quantity, sf::Texture texture);

    /**
     * @brief Remove a specified quantity of an item from the inventory.
     * @param itemName The name of the item to remove.
     * @param quantity The quantity of the item to be removed.
     * @return True if the specified quantity of the item was successfully removed, false otherwise.
     */
    bool removeItem(const std::string& itemName, int quantity);

    /**
     * @brief Get the count of a specific item in the inventory.
     * @param item The item to count.
     * @return The count of the item in the inventory.
     */
    int getItemCount(const std::string& itemName);

    /**
     * @brief Display the inventory contents.
     */
    void displayInventory();

    /**
     * @brief Get the current size of the inventory.
     * @return The size of the inventory.
     */
    int getInventorySize();

    /**
     * @brief Clear all items from the inventory.
     */
    void clearInventory();

    /**
     * @brief Draws the inventory to the top left of view.
     * @param window The windows of the game.
     * @return Vector of CircleShapes to draw on the view.
     */
    std::vector<sf::CircleShape> Draw(sf::RenderWindow& window);
};

#endif // INVENTORY_HPP
