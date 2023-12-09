//
// Created by dannypa on 05.11.23.
//

#ifndef DUNGEONCRAWLER_CHARACTER_H
#define DUNGEONCRAWLER_CHARACTER_H

#include <algorithm>
#include <string>
#include <iostream>
#include "../inventory.hpp"
#include "SFML/Graphics.hpp"
#include "../helper.hpp"
#include "../room.hpp"
#include "../textureManager.hpp"

// Constants
const float CREATURE_SIZE = 1.0f;
const float HEALTH_BAR_START_WIDTH = 0.3f;
const float HEALTH_BAR_HEIGHT = 0.2f;

/// @brief Base class for every "alive" entity in the dungeon.
class Creature {
 public:
  /// @brief The constructor.
  /// @param type type of the creature
  /// @param name name of the creature
  /// @param maxHealth maximum health of the creature
  /// @param maxVelocity maximum velocity of the creature
  /// @param initialPos initial position of the creature
  /// @param window window the creature is going to be drawn
  /// @param room room the creature is initially in
  /// @param base_damage the damage that creature does without any items
  /// @param t texture of the creature
  /// @param logger the stream to log info to
  /// @param inventory inventory of the creature
  Creature(const std::string &type,
           const std::string &name,
           int maxHealth,
           float maxVelocity,
           const sf::Vector2<float> &initialPos,
           sf::RenderWindow &window,
           const Room &room,
           int base_damage,
           sf::Texture &t,
           std::ostream &logger = std::cout,
           const Inventory &inventory = Inventory());

  /// @brief Checks if the creature is alive.
  /// @return true if the creature is alive, false otherwise
  [[nodiscard]] bool IsAlive() const { return health_ > 0; }

  /// @return description_
  [[nodiscard]] const std::string &GetDescription() const;

  /// @brief Handles the logic when this creature is attacked.
  /// @param base_damage Base attack damage (actual damage may be later recalculated somehow)
  /// @param c2 the creature who attacks
  /// @return the damage taken
  float TakeHit(float base_damage, const Creature &c2);

  /// @brief Attacks another creature with a given item
  /// @param c2 The creature to attack
  /// @param sword The item to attack with; if sword = {}, no buffs are applied
  /// @return damage dealt
  float Attack(Creature &c2, const Sword &sword = {}) const;

  /// @brief Updates state of the creature.
  /// Later probably need to pass something cleverer, like game class, tho i am not sure yet.
  virtual void Update();

  /// @brief Draws the creature's sprite in a given window.
  /// @param camera current camera state
  void Draw();

  /// @brief Setter for velocity.
  /// @param newVelocity
  void SetVelocity(const sf::Vector2<float> &newVelocity);

  /// @brief Sets x velocity.
  /// @param nvx new x velocity.
  void SetVelocityX(float nvx);

  /// @brief Sets y velocity.
  /// @param nvy new y velocity.
  void SetVelocityY(float nvy);

  /// @brief Sets texture
  /// @param t new texture
  void SetTexture(const sf::Texture &t);

  /// @brief Sets position
  /// @param position new position
  virtual void SetPosition(const sf::Vector2<float> &position);

  /// @brief Sets room; will be overriden by player so that changing rooms spawns monsters
  /// @param room new room
  virtual void SetRoom(Room &room);

  /// @brief draws the healthbar of the creature
  /// @param window the window where the healthbar is drawn to
  void DrawHealthBar(sf::RenderWindow &window);

  /// @return position
  const sf::Vector2<float> &GetPosition() const;

  /// @return current room
  const Room &GetRoom() const;

  /// @return inventory_ of the creture
  Inventory &GetInventory();

 protected:
  /// @brief max movement speed of the creature\nNote: this is the limit for vx and vy separately.
  const float maxVelocity_;

  /// @brief max health of the creature
  const float maxHealth_;

  /// @brief current health of the creature.
  float health_;

  /// @brief damage that creature deals with no items
  int base_damage_;

  /// @brief type of the character (e.g. monster)
  const std::string type_;

  /// @brief name of the character
  std::string name_;

  /// @brief description in the format "Creature of type <type_> named <name>"
  std::string description_;

  /// @brief the inventory_ of the creature
  Inventory inventory_;

  /// @brief texture
  sf::Texture &texture_;

  /// @brief position of the creature on the screen
  sf::Vector2<float> position_;

  /// @brief current velocity of the creature
  sf::Vector2<float> velocity_;

  /// @brief window in which the creature is supposed to be drawn
  sf::RenderWindow &window_;

  /// @brief stream to log information about the class.
  std::ostream &logger_;

  /// @brief room the creature is in.
  Room room_;

  /// @brief The rectangle representing the creature.
  sf::RectangleShape creatureRect_;

  /// @brief Reduces health by damage. If damage is greater then health, sets health to 0.
  /// @param damage amount to reduce health_ by
  void TakeDamage_(float damage);

  /// @brief Returns the rooms the creature can go too. By default returns only current room; however,
  /// if the creature is a player and the monsters are cleared the next room is also available.
  /// @return
  virtual std::vector<Room> GetAvailableRooms();

  /// @brief Updates position based on current position, velocity and available rooms. If position + velocity is in
  /// one of the available rooms then the position is updated, if not then it stays the same.
  void UpdatePosition();

  /// @brief Updated rotation so that the creatures faces the direction it is supposed to face, as specified by
  /// GetFacingDirection() .
  void UpdateRotation();

  /// @brief Returns the facing direction of the creature; the default case is just face the direction of moving;
  /// however, the Player class overrides the function and Player objects face the cursor.
  /// @return The vector specifying the direction the creature should face.
  virtual sf::Vector2f GetFacingDirection();

  /// @brief Turns the creature to the direction of the vector (dx, dy)
  /// @param dx x coordinate of the turn vector
  /// @param dy y coordinate of the turn vector
  void TurnToDirection(float dx, float dy);
};

#endif //DUNGEONCRAWLER_CHARACTER_H
