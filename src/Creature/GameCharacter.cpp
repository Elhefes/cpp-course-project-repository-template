//
// Created by dannypa on 27.11.23.
//
#include "GameCharacter.hpp"

void Monster::tick(Player &p) {
  if (clock() - lastTick_ < TICK_TIME) return;
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

void Monster::SpawnMonsters(Room &room, sf::RenderWindow &window, std::vector<Monster *> &res) {
  if (room.isCorridor()) return;

  // TODO: if room is already completed do not spawn anyone
  const int MONSTER_NUMBER = 5; // TODO: set this to be a room parameter
  const int MONSTER_HEALTH = 10;
  const float MONSTER_VELOCITY = 0.1f;
  for (int _ = 0; _ < MONSTER_NUMBER; _++) {
    std::string type = "random type later ig";
    std::string name = "random name later ig";
    auto pos = room.randomPos();
    res.push_back(new Monster(type, name, MONSTER_HEALTH, MONSTER_VELOCITY,
                              pos, window, room));
  }
}

void Player::SetRoom(Room &room, std::vector<Monster *> &monsters) {
  room_ = room;
  Monster::SpawnMonsters(room, window_, monsters);
}

