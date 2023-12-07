//
// Created by dannypa on 13.11.23.
//

#ifndef DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
#define DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
#include <unordered_set>
#include "Creature.hpp"
#include "../room.hpp"
#include "../helper.hpp"

const long TICK_TIME = CLOCKS_PER_SEC / 2;

class Player;
// MONSTER
const float ATTACK_RADIUS = 2.f;
class Monster : public Creature {
 public:
  Monster(const std::string &type,
          const std::string &name,
          int max_health,
          float max_velocity,
          const sf::Vector2<float> &initial_pos,
          sf::RenderWindow &window,
          const Room &room,
          int base_damage,
          sf::Texture &texture,
          std::ostream &logger = std::cout,
          Inventory inventory = Inventory()) : Creature(type,
                                                        name,
                                                        max_health,
                                                        max_velocity,
                                                        initial_pos,
                                                        window,
                                                        room, base_damage, texture,
                                                        logger,
                                                        inventory) {}

  void tick(Player &p);
 private:
  long lastTick_ = 0;
};

// PLAYER
class Player : public Creature {
 public:
  Player(const std::string &type, const std::string &name, int maxHealth, float maxVelocity,
         const sf::Vector2<float> &initialPos,
         sf::RenderWindow &window,
         Room room,
         sf::Texture &texture,
         std::ostream &logger = std::cout,
         Inventory inventory = Inventory()) :
      Creature(type, name, maxHealth, maxVelocity, initialPos, window, room, 25, texture, logger, inventory) {};

  /// @brief Special ability of each player class
  void Special() {};
  void SetPosition(const sf::Vector2<float> &position) override {
    position_ = position;
  }

  sf::Vector2f getPosition() {
    return position_;
  }

  void SetRoom(Room &room) override {
    room_ = room;
    UpdateRoomIndex_();
  };

  void SetRoom(Room &room, std::vector<Monster *> &monsters, std::vector<sf::Vector2f> &potionPos);

  void Update(std::vector<Monster *> &monsters, std::vector<sf::Vector2f> potions) {
    auto old = room_;
    Creature::Update();
    if (room_ != old) {
      SpawnMonsters(window_, monsters);
      SpawnPotion(potions);
    }
  }

  void SetRooms(const std::vector<Room> &rooms) {
    rooms_ = rooms;
    UpdateRoomIndex_();
  }

  void SetMonstersCleared(bool monstersCleared) {
    monstersCleared_ = monstersCleared;
  }

  void SetItemInUse(int index) {
    if (index >= inventory_.getSize()) return;
    else itemInUse = index;
  }

  int GetItemInUse() {
    return itemInUse;
  }

  void tryHealing() {
    if (!inventory_.IsSword(itemInUse)) {
      float amountToHeal = inventory_.GetHealingAmount(itemInUse);
      float old = health_;
      health_ = std::min(maxHealth_, health_ + amountToHeal);
      std::cout << "Player healed from " << old << " to " << health_ << std::endl;
    }
  }

  std::vector<Room> GetAvailableRooms() override {
    std::vector<Room> res = {room_};
    if (monstersCleared_) {
      if (roomIndex_ + 1 < rooms_.size()) res.push_back(rooms_[roomIndex_ + 1]);
    }
    return res;
  }

  void TryAttack(const std::vector<Monster *> &monsters) {
    int ind = 0;
    for (int i = 1; i < monsters.size(); i++) {
      if (monsters[i]->IsAlive() && help::square(monsters[i]->GetPosition() - GetPosition())
          < help::square(monsters[ind]->GetPosition() - GetPosition())) {
        ind = i;
      }
    }
    if (!monsters.empty() && help::close(monsters[ind]->GetPosition(), GetPosition(), ATTACK_RADIUS)) {
      if (itemInUse >= inventory_.getSize() || !inventory_.IsSword(itemInUse)) Attack(*monsters[ind]);
      else {
        Attack(*monsters[ind], inventory_.GetSword(itemInUse));
      }
    }
  }

  sf::Vector2f GetFacingDirection() override {
    sf::Vector2f curPos = creatureRect.getPosition();
    sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition(window_));
    return position - curPos;
  }

  void TryPickup(std::vector<sf::Vector2f> &potionPositions) {
    int ind = 0;
    for (int i = 1; i < potionPositions.size(); i++) {
      if (help::square(potionPositions[i] - position_) < help::square(potionPositions[ind] - position_)) {
        ind = i;
      }
    }
    if (ind < potionPositions.size() && help::len(potionPositions[ind] - position_) <= ATTACK_RADIUS) {
      potionPositions.erase(potionPositions.begin() + ind);
      inventory_.addPotion(HealthPotion(), 1);
    }
  }

  void SpawnMonsters(sf::RenderWindow &window, std::vector<Monster *> &res);
  void SpawnPotion(std::vector<sf::Vector2f> &pos) {
    // spawns with probability 1/3
    if (rand() % 3 != 0) return; // spawns just one for now, but can be easily changed to spawn more
    pos.push_back(room_.randomPos(1.f));
  }

 private:
  int itemInUse = 0;
  std::vector<Room> rooms_;
  int roomIndex_;
  bool monstersCleared_;

  void UpdateRoomIndex_() {
    Room tmp = room_;
    roomIndex_ = int(std::find_if(rooms_.begin(),
                                  rooms_.end(),
                                  [tmp](const Room &b) { return tmp.getId() == b.getId(); })
                         - rooms_.begin());
  }
};

#endif //DUNGEONCRAWLER_SRC_CREATURE_GAMECHARACTERS_HPP_
