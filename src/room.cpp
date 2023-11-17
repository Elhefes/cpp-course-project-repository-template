#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>


class Room {
public:
    int x, y, width, height;

    std::vector<std::vector<sf::Texture>> tileColors;

    Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
        tileColors.resize(abs(width), std::vector<sf::Texture>(abs(height)));
        for (int i = 0; i < abs(width); ++i) {
            for (int j = 0; j < abs(height); ++j) {
                sf::Texture texture;

                texture.loadFromFile("../assets/textures/room_floor1.png");

                tileColors[i][j] = texture;
            }
        }
    }
private:
    sf::Color getRandomColor() {
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}
};