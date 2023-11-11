#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>


class Room {
public:
    int x, y, width, height;

    std::vector<std::vector<sf::Color>> tileColors;

    Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
        tileColors.resize(width, std::vector<sf::Color>(height));
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                tileColors[i][j] = getRandomColor();
            }
        }
    }
private:
    sf::Color getRandomColor() {
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}
};