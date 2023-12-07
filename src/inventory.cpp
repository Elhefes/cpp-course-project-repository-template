/*
#include "inventory.hpp"

void Inventory::addItem(const std::string& itemName, int quantity, sf::Texture texture) {
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

bool Inventory::removeItem(const std::string& itemName, int quantity) {
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

int Inventory::getItemCount(const std::string& itemName) {
    int count = 0;
        for (const auto& item : items) {
            if (std::get<0>(item) == itemName) {
                count += std::get<1>(item);
            }
        }
        return count;
}

void Inventory::displayInventory() {
    std::cout << "Inventory:\n";
        for (const auto& item : items) {
            std::cout << std::get<0>(item) << " - Quantity: " << std::get<1>(item) << "\n";
        }
}

int Inventory::getInventorySize() {
    return items.size();
}

void Inventory::clearInventory() {
    items.clear();
}

std::vector<sf::CircleShape> Inventory::Draw(sf::RenderWindow& window) {
    std::vector<sf::CircleShape> circles;
        for (int i = 0; i < items.size(); ++i) {

            // Draws the circles
            sf::CircleShape circle(0.5f);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(0.1f);
            circle.setOutlineColor(sf::Color::Blue);
            sf::Vector2f center = window.getView().getCenter();
            float x = center.x - window.getView().getSize().x / 2 + 0.5 + (i * 1.5f);
            float y = center.y - window.getView().getSize().y / 2 + 0.5;
            std::cout << x << "  " << y << std::endl;
            circle.setPosition(sf::Vector2f(x, y));

            // Draws the items inside the circles
            sf::Vector2f circleCenter(circle.getPosition());
            sf::Sprite sprite(std::get<2>(items[i]));
            sf::FloatRect itemBounds = sprite.getGlobalBounds();
            float scale = (2.0f * circle.getRadius()) / std::max(itemBounds.width, itemBounds.height);
            sprite.setScale(sf::Vector2f(scale, scale));
            sprite.setPosition(circleCenter);

            // If items count is more than one draws the amount of the item on the top right of the circle
            if (std::get<1>(items[i]) > 1) {
                std::string amount = std::to_string(std::get<1>(items[i]));
                sf::Text quantityText(font);
                quantityText.setString(amount);
                quantityText.setFillColor(sf::Color::White);
                quantityText.setScale(sf::Vector2f(circle.getRadius() / 10, circle.getRadius() / 20));
                quantityText.setPosition(sf::Vector2f(circleCenter.x + circle.getRadius() * 2, circleCenter.y - circle.getRadius() / 2));
                window.draw(quantityText);
            }
            
            window.draw(sprite);
            circles.push_back(circle);
        }
        return circles;
}
*/