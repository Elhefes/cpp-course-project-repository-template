#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "Item.hpp"
#include <SFML/Graphics.hpp>

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
     */
    void addItem(const std::string& itemName, int quantity, sf::Texture texture) {
    bool found = false;
    for (auto& item : items) {
        if (std::get<0>(item) == itemName) {
            std::get<1>(item) += quantity; // Update quantity if item exists
            found = true;
            break;
        }
    }
    if (!found) {
        items.emplace_back(itemName, quantity, texture); // Add new item otherwise
    }
    }


    /**
     * @brief Remove a specified quantity of an item from the inventory.
     * @param itemName The name of the item to remove.
     * @param quantity The quantity of the item to be removed.
     * @return True if the specified quantity of the item was successfully removed, false otherwise.
     */
    bool removeItem(const std::string& itemName, int quantity) {
        for (auto& item : items) {
            if (std::get<0>(item) == itemName) {
                if (std::get<1>(item) < quantity) {
                    return false; // Insufficient quantity to remove
                } else {
                    std::get<1>(item) -= quantity; // Update quantity if item exists
                    return true; // Successfully removed the specified quantity of the item
                }
            }
        }
        return false; // Item not found
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
    int getItemCount(const std::string& itemName) {
        int count = 0;
        for (const auto& item : items) {
            if (std::get<0>(item) == itemName) {
                count += std::get<1>(item);
            }
        }
        return count;
    }

    /**
     * @brief Display the inventory contents.
     */
    void displayInventory() {
        std::cout << "Inventory:\n";
        for (const auto& item : items) {
            std::cout << std::get<0>(item) << " - Quantity: " << std::get<1>(item) << "\n";
        }
    }

    /**
     * @brief Get the current size of the inventory.
     * @return The size of the inventory.
     */
    int getInventorySize() {
        return items.size();
    }

    /**
     * @brief Clear all items from the inventory.
     */
    void clearInventory() {
        items.clear();
    }

    std::vector<sf::CircleShape> Draw(sf::RenderWindow& window) {
        std::vector<sf::CircleShape> circles;
        for (int i = 0; i < items.size(); ++i) {
            sf::CircleShape circle(0.5f);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(0.1f);
            circle.setOutlineColor(sf::Color::Blue);
            sf::Vector2f center = window.getView().getCenter();
            float x = center.x - window.getView().getSize().x / 2 + 0.5 + (i * 1.3f);
            float y = center.y - window.getView().getSize().y / 2 + 0.5;
            std::cout << x << "  " << y << std::endl;
            circle.setPosition(sf::Vector2f(x, y));
            sf::Vector2f circleCenter(circle.getPosition());
            sf::Sprite sprite(std::get<2>(items[i]));
            sf::FloatRect itemBounds = sprite.getGlobalBounds();
            //sprite.setOrigin(sf::Vector2f(itemBounds.width / 2, itemBounds.height / 2));
            float scale = (2.0f * circle.getRadius()) / std::max(itemBounds.width, itemBounds.height);
            sprite.setScale(sf::Vector2f(scale, scale));
            sprite.setPosition(circleCenter);
            window.draw(sprite);
            circles.push_back(circle);
        }
        return circles;
}


};

#endif // INVENTORY_HPP
