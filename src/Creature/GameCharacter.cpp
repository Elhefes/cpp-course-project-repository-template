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
//  if (room.IsCorridor()) return;
//
//  // TODO: if room is already completed do not spawn anyone
////  const int MONSTER_NUMBER = 0; // TODO: set this to be a room parameter
//  int monster_number = 1 + rand() % ()
//  const int MONSTER_HEALTH = 10;
//  const float MONSTER_VELOCITY = 0.1f;
//  for (int _ = 0; _ < MONSTER_NUMBER; _++) {
//    std::string type = "random type later ig";
//    std::string name = "random name later ig";
//    auto pos = room.RandomPos(1.f);
//    res.push_back(new Monster(type, name, MONSTER_HEALTH, MONSTER_VELOCITY,
//                              pos, window, room));
//  }
//}

void Player::SetRoom(Room &room, std::vector<Monster *> &monsters, std::vector<sf::Vector2f> &potionPos) {
  SetRoom(room);
  SpawnMonsters(monsters);
  SpawnPotion(potionPos);
}
void Player::SpawnMonsters(std::vector<Monster *> &res) {
  if (room_.IsCorridor()) return;

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
    auto pos = room_.RandomPos(1.f);
    res.push_back(new Monster(type, name, monster_health, monster_velocity,
                              pos, window_, room_, (int) damage, texture));
  }
}

int Player::GetRoomIndex() {
  return roomIndex_;
}
sf::Vector2f Player::GetPosition() {
  return position_;
}
void Player::SetRoom(Room &room) {
  room_ = room;
  UpdateRoomIndex();
}
void Player::Update(std::vector<Monster *> &monsters, std::vector<sf::Vector2f> potions) {
  auto old = room_;
  Creature::Update();
  if (room_ != old) {
    SpawnMonsters(monsters);
    SpawnPotion(potions);
  }
}
void Player::SetRooms(const std::vector<Room> &rooms) {
  rooms_ = rooms;
  UpdateRoomIndex();
}
void Player::SetMonstersCleared(bool monstersCleared) {
  monstersCleared_ = monstersCleared;
}
void Player::SetItemInUse(int index) {
  if (index >= inventory_.GetSize()) return;
  else itemInUse = index;
}
int Player::GetItemInUse() const {
  return itemInUse;
}
void Player::TryHealing() {
  if (!inventory_.IsSword(itemInUse)) {
    float amountToHeal = inventory_.GetHealingAmount(itemInUse);
    float old = health_;
    health_ = std::min(maxHealth_, health_ + amountToHeal);
    std::cout << "Player healed from " << old << " to " << health_ << std::endl;
  }
}
std::vector<Room> Player::GetAvailableRooms() {
  std::vector<Room> res = {room_};
  if (monstersCleared_) {
    if (roomIndex_ + 1 < rooms_.size()) res.push_back(rooms_[roomIndex_ + 1]);
  }
  return res;
}
void Player::TryAttack(const std::vector<Monster *> &monsters) {
  int ind = 0;
  for (int i = 1; i < monsters.size(); i++) {
    if (monsters[i]->IsAlive() && help::square(monsters[i]->GetPosition() - GetPosition())
        < help::square(monsters[ind]->GetPosition() - GetPosition())) {
      ind = i;
    }
  }
  if (!monsters.empty() && help::close(monsters[ind]->GetPosition(), GetPosition(), ATTACK_RADIUS)) {
    if (itemInUse >= inventory_.GetSize() || !inventory_.IsSword(itemInUse)) Attack(*monsters[ind]);
    else {
      Attack(*monsters[ind], inventory_.GetSword(itemInUse));
    }
  }
}
sf::Vector2f Player::GetFacingDirection() {
  sf::Vector2f curPos = creatureRect_.getPosition();
  sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition(window_));
  return position - curPos;
}
void Player::TryPickup(std::vector<sf::Vector2f> &potionPositions) {
  int ind = 0;
  for (int i = 1; i < potionPositions.size(); i++) {
    if (help::square(potionPositions[i] - position_) < help::square(potionPositions[ind] - position_)) {
      ind = i;
    }
  }
  if (ind < potionPositions.size() && help::len(potionPositions[ind] - position_) <= ATTACK_RADIUS) {
    potionPositions.erase(potionPositions.begin() + ind);
    inventory_.AddPotion(HealthPotion(), 1);
  }
}
void Player::SpawnPotion(std::vector<sf::Vector2f> &pos) {
  // spawns with probability 1/3
  if (rand() % 3 != 0) return; // spawns just one for now, but can be easily changed to spawn more
  pos.push_back(room_.RandomPos(1.f));
}
void Player::UpdateRoomIndex() {
  Room tmp = room_;
  roomIndex_ = int(std::find_if(rooms_.begin(),
                                rooms_.end(),
                                [tmp](const Room &b) { return tmp.GetId() == b.GetId(); })
                       - rooms_.begin());
}
