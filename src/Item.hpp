//
// Created by dannypa on 06.11.23.
//

#ifndef DUNGEONCRAWLER_SRC_ITEM_HPP_
#define DUNGEONCRAWLER_SRC_ITEM_HPP_

#include <iostream>

class Item {
private:
    std::string name;
    int quantity;

public:
    Item(const std::string& itemName) : name(itemName) {}

    std::string getName() const { return name; }
};

#endif //DUNGEONCRAWLER_SRC_ITEM_HPP_
