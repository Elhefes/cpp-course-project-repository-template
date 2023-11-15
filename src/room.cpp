#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>


class Room {
public:
    int x, y, width, height;

    std::vector<std::vector<sf::Texture>> tileTextures;

    Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
        loadTextures();
        tileTextures.resize(width, std::vector<sf::Texture>(height));
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                tileTextures[i][j] = getRandomTexture();
            }
        }
    }
private:
    const std::string TEXTURES_PATH = "../assets/textures/";
    sf::Texture texture1;
    sf::Texture texture2;

    void loadTextures() {
        if (!texture1.loadFromFile(TEXTURES_PATH + "room_floor1.png")) {
            std::cerr << "Error loading room_floor1.png" << std::endl;
            return;
        }
            if (!texture2.loadFromFile(TEXTURES_PATH + "room_floor2.png")) {
            std::cerr << "Error loading room_floor2.png" << std::endl;
            return;
        }
    }

    sf::Texture getRandomTexture() {
        int random = rand() % 2;
        if (random == 1) {
            return texture2;
        }
        return texture1;
    }
};