#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "room.hpp"


Room::Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    tileTextures.resize(abs(width), std::vector<sf::Texture*>(abs(height)));

    for (int i = 0; i < abs(width); ++i) {
        for (int j = 0; j < abs(height); ++j) {
            short int random = dis(gen);

            if (random == 1) {
                tileTextures[i][j] = &room_t1;
            } else {
                tileTextures[i][j] = &room_t2;
            }
        }
    }
}

Room::~Room() {
    }
