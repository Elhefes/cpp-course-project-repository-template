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

/// @brief Base class for every "alive" entity in the dungeon
class Creature {
 public:
  Creature(const std::string &type,
           const std::string &name,
           int maxHealth,
           float maxVelocity,
           const sf::Vector2<float> &initialPos,
           sf::RenderWindow &window,
           const Room &room,
           int base_damage,
           std::ostream &logger = std::cout,
           const sf::CircleShape &sprite = sf::CircleShape(50),
           const Inventory &inventory = Inventory());

  /// @brief Checks if the creature is alive.
  /// @return true if the creature is alive, false otherwise
  [[nodiscard]] bool IsAlive() const { return health_ > 0; }

  /// @return description_
  [[nodiscard]] const std::string &GetDescription() const;
  [[nodiscard]] const std::string &GetType() const;

  /// @brief Handles the logic when this creature is attacked.
  /// @param base_damage Base attack damage (actual damage may be later recalculated somehow)
  /// @param c2 the creature who attacks
  /// @return the damage taken
  int TakeHit(float base_damage, const Creature &c2);

  int Attack(Creature &c2, const Sword &sword = {}) const;

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
  void SetHealth(float health);
  void SetSprite(const sf::CircleShape &sprite);
  virtual void SetPosition(const sf::Vector2<float> &position);
  virtual void SetRoom(Room &room);
  /// @brief draws the healthbar of the creature
  /// @param window the window where the healthbar is drawn to
  void DrawHealthBar(sf::RenderWindow &window);

  /// @return inventory
  const Inventory &GetInventory() const;
  /// @return position
  const sf::Vector2<float> &GetPosition() const;
  /// @return max velocity
  float GetMaxVelocity() const;
  /// @return velocity
  const sf::Vector2<float> &GetVelocity() const;
  /// @return current room
  const Room &GetRoom() const;
  /// @return inventory of the creture
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
  /// @brief the inventory of the creature
  Inventory inventory_;
  /// @brief change to actual sprite later
  sf::CircleShape sprite_;
  /// @brief position of the creature on the screen
  sf::Vector2<float> position_;
  /// @brief current velocity of the creature
  sf::Vector2<float> velocity_;
  /// @brief window in which the creature is supposed to be drawn
  sf::RenderWindow &window_;
  /// @brief stream to log information about the class
  std::ostream &logger_;
  /// @brief room the creature is in

  sf::RectangleShape creatureRect;
  Room room_;

  /// @brief Reduces health by damage. If damage is greater then health, sets health to 0.
  /// @param damage amount to reduce health_ by
  void TakeDamage_(float damage) { health_ = std::max(0.f, health_ - damage); }

  virtual std::vector<Room> GetAvailableRooms();
  void UpdatePosition();
  void UpdateRotation();
  virtual sf::Vector2f GetFacingDirection();
  void TurnToDirection(float dx, float dy);
};

#endif //DUNGEONCRAWLER_CHARACTER_H
