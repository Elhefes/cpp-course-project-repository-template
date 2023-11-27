#ifndef ROOM_HPP
#define ROOM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "textureManager.hpp"
#include "helper.hpp"

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
    Room(int x, int y, int width, int height, bool isCorridor);

    ~Room();

    int x; /**< X-coordinate of the room. */
    int y; /**< Y-coordinate of the room. */
    int width; /**< Width of the room. */
    int height; /**< Height of the room. */
    bool operator==(const Room &other) const { return id_ == other.id_; }
    bool operator!=(const Room &other) const { return id_ != other.id_; }


    std::vector<std::vector<sf::Texture*>> tileTextures; /**< 2D vector storing the tile textures of the room. */

    [[nodiscard]] bool isCorridor() const { return isCorridor_; }

  [[nodiscard]] sf::Vector2f randomPos() const {
    return {(float) randInt(x, x + width) * 1.f, (float) randInt(y, y + height)};
  }

private:
  /// @brief checks if the room is a corridor
  bool isCorridor_;
  /// @brief room id.
  int id_;
  static int randInt(int a, int b) {
    return a + rand() % (b - a);
  }
};

#endif
