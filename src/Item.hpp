#ifndef DUNGEONCRAWLER_SRC_ITEM_HPP_
#define DUNGEONCRAWLER_SRC_ITEM_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

class Item {
private:
    std::string name_;
    sf::Texture texture_;

public:
    Item(const std::string& itemName, const sf::Texture texture) : name_(itemName), texture_(texture) {}

    std::string getName() const { return name_; }
    sf::Texture getTexture() const { return texture_; }
};

#endif //DUNGEONCRAWLER_SRC_ITEM_HPP_
