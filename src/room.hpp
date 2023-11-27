#ifndef ROOM_HPP
#define ROOM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "textureManager.hpp"

/**
 * @brief Class representing a Room in the game.
 */
class Room {
public:
    /**
     * @brief Constructor for the Room class.
     *
     * @param x X-coordinate of the room.
     * @param y Y-coordinate of the room.
     * @param width Width of the room.
     * @param height Height of the room.
     */
    Room(int x, int y, int width, int height);

    int x; /**< X-coordinate of the room. */
    int y; /**< Y-coordinate of the room. */
    int width; /**< Width of the room. */
    int height; /**< Height of the room. */

    std::vector<std::vector<sf::Texture*>> tileTextures; /**< 2D vector storing the tile textures of the room. */
};

#endif
