#ifndef ROOM_HPP
#define ROOM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

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

    ~Room();

    int x; /**< X-coordinate of the room. */
    int y; /**< Y-coordinate of the room. */
    int width; /**< Width of the room. */
    int height; /**< Height of the room. */

    std::vector<std::vector<sf::Color>> tileColors; /**< 2D vector storing the tile colors of the room. */

private:

    /**
     * @brief Generates a random color for the room.
     *
     * @return sf::Color A randomly generated color.
     */
    sf::Color getRandomColor();
};

#endif
