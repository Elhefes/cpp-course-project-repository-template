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

  [[nodiscard]] int getId() const {
    return id_;
  }

  /// @brief Checks if the entity is inside the room. Additionally returns multipliers for velocity:
  /// if the entity is near the borders of the room, then the needed speed is multiplied by -1.
  /// @param pos position of the entity
  /// @param radius size of the entity
  /// @return tuple: boolean value (true if the entity is inside) and pair of speed multipliers
  [[nodiscard]] std::tuple<bool, float, float, sf::Vector2f> isInside(sf::Vector2f pos, float sz) const {
    const float EPS = 0.1;
    auto xMin = (float) x /*+ sz / 2*/, xMax = (float) (x + std::abs(width)) /*- sz / 2*/;
    auto yMin = (float) y /*+ sz / 2*/, yMax = (float) (y + std::abs(height)) /*- sz / 2*/;
    bool flag = (xMin <= pos.x && pos.x <= xMax && yMin <= pos.y && pos.y <= yMax);
    float xMul = 1, yMul = 1;
    if (help::close(pos.x, yMin, EPS) || help::close(pos.x, xMax, EPS)) xMul *= -1;
    if (help::close(pos.y, yMin, EPS) || help::close(pos.y, yMax, EPS)) yMul *= -1;
    pos.x = bound(pos.x, xMin, xMax, 0.9f * EPS);
    pos.y = bound(pos.y, yMin, xMax, 0.9f * EPS);
    return {flag, xMul, yMul, pos};
  }

  std::vector<std::vector<sf::Texture *>> tileTextures; /**< 2D vector storing the tile textures of the room. */

  [[nodiscard]] bool isCorridor() const { return isCorridor_; }

  [[nodiscard]] sf::Vector2f randomPos(float sz) const {
    return {(float) randInt(x + sz / 2, x + width - sz / 2), (float) randInt(y + sz / 2, y + height - sz / 2)};
  }

 private:
  /// @brief checks if the room is a corridor
  bool isCorridor_;
  /// @brief room id.
  int id_;
  static int randInt(int a, int b) {
    if (b == a) return a; // shouldnt be like that, but it is what it is
    return a + rand() % (b - a);
  }
};

#endif
