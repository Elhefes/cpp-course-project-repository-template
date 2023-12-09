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

  [[nodiscard]] int GetId() const { return id_; };

  /// @brief Checks if the entity is inside the room. Additionally returns multipliers for velocity:
  /// if the entity is near the borders of the room, then the needed speed is multiplied by -1.
  /// @param pos position of the entity
  /// @param radius size of the entity
  /// @return tuple: boolean value (true if the entity is inside) and pair of speed multipliers
  [[nodiscard]] std::tuple<bool, float, float, sf::Vector2f> IsInside(sf::Vector2f pos, float sz) const;

  std::vector<std::vector<sf::Texture *>> tileTextures; /**< 2D vector storing the tile textures of the room. */

  [[nodiscard]] bool IsCorridor() const { return isCorridor_; }

  [[nodiscard]] sf::Vector2f RandomPos(float sz) const;

 private:
  /// @brief checks if the room is a corridor
  bool isCorridor_;
  /// @brief room id.
  int id_;

  static int RandInt(int a, int b);
};

#endif
