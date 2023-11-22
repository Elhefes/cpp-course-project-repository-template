#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "room.hpp"

Room::Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    tileColors.resize(abs(width), std::vector<sf::Color>(abs(height)));
    for (int i = 0; i < abs(width); ++i) {
        for (int j = 0; j < abs(height); ++j) {
            tileColors[i][j] = getRandomColor();
        }
    }
}

sf::Color Room::getRandomColor() {
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}