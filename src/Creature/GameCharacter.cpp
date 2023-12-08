//
// Created by dannypa on 27.11.23.
//
#include "GameCharacter.hpp"

void Monster::tick(Player &p) {
  if (clock() - lastTick_ < TICK_TIME || !IsAlive()) return;
  lastTick_ = clock();
  // check if the player is in the same room
  if (p.GetRoom() != room_) {
    return;
  }
  sf::Vector2 v = (p.GetPosition() - position_);
  if (rand() % 3 == 0) v.x *= -1;
  if (rand() % 3 == 0) v.y *= -1;
  v /= (float) help::len(v);
  v *= maxVelocity_;
  SetVelocity(v);
  if (help::close(position_, p.GetPosition(), (float) ATTACK_RADIUS)) {
    Attack(p);
  }
}

//void Monster::SpawnMonsters(Room &room, sf::RenderWindow &window, std::vector<Monster *> &res) {
//  if (room.isCorridor()) return;
//
//  // TODO: if room is already completed do not spawn anyone
////  const int MONSTER_NUMBER = 0; // TODO: set this to be a room parameter
//  int monster_number = 1 + rand() % ()
//  const int MONSTER_HEALTH = 10;
//  const float MONSTER_VELOCITY = 0.1f;
//  for (int _ = 0; _ < MONSTER_NUMBER; _++) {
//    std::string type = "random type later ig";
//    std::string name = "random name later ig";
//    auto pos = room.randomPos(1.f);
//    res.push_back(new Monster(type, name, MONSTER_HEALTH, MONSTER_VELOCITY,
//                              pos, window, room));
//  }
//}

void Player::SetRoom(Room &room, std::vector<Monster *> &monsters, std::vector<sf::Vector2f> &potionPos) {
  SetRoom(room);
  SpawnMonsters(window_, monsters);
  SpawnPotion(potionPos);
}
void Player::SpawnMonsters(sf::RenderWindow &window, std::vector<Monster *> &res) {
  if (room_.isCorridor()) return;

  int monster_number = 1 + roomIndex_ / 2 + rand() % (roomIndex_ + 1);
  float damage = 10;
  int monster_health = 60;
  float monster_velocity = 0.085f;
  sf::Texture &texture = assassin_t;
  if (roomIndex_ + 1 == rooms_.size()) {
    monster_number = 1;
    monster_health = 250;
    monster_velocity = 0.07f;
    damage *= 1.5;
    texture = boss_t;
  }
  for (int _ = 0; _ < monster_number; _++) {
    std::string type = "random type later ig";
    std::string name = "random name later ig";
    auto pos = room_.randomPos(1.f);
    res.push_back(new Monster(type, name, monster_health, monster_velocity,
                              pos, window, room_, (int) damage, texture));
  }
}

int Player::getRoomIndex() {
  return roomIndex_;
}