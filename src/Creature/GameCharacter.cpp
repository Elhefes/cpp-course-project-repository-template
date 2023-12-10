//
// Created by dannypa on 27.11.23.
//
#include "GameCharacter.hpp"

/// @return returns true with the given probability
bool RandomEvent(float probability) {
  // todo: i know that we are not supposed to use this random, but it's too late now
  return ((float) rand() / RAND_MAX < probability);
}

void Monster::tick(Player &p) {
  if (clock() - lastTick_ < TICK_TIME || !IsAlive()) return;
  lastTick_ = clock();
  // check if the player is in the same room
  if (p.GetRoom() != room_) {
    return;
  }
  sf::Vector2 v = (p.GetPosition() - position_);
  if (RandomEvent(MONSTER_DIRECTION_CHANGE_PROBABILITY)) v.x *= -1;
  if (RandomEvent(MONSTER_DIRECTION_CHANGE_PROBABILITY)) v.y *= -1;
  v /= (float) help::len(v);
  v *= maxVelocity_;
  SetVelocity(v);
  if (help::close(position_, p.GetPosition(), (float) MONSTER_ATTACK_RADIUS)) {
    Attack(p);
  }
}

void Player::SetRoom(Room &room, std::vector<Monster *> &monsters, std::vector<sf::Vector2f> &potionPos) {
  SetRoom(room);
  SpawnMonsters(monsters);
  SpawnPotion(potionPos);
}

void Player::SpawnMonsters(std::vector<Monster *> &res) {
  if (room_.IsCorridor()) return;

  int monster_number = 1 + roomIndex_ / 2 + rand() % (roomIndex_ + 1);
  float damage = DEFAULT_MONSTER_DAMAGE;
  int monster_health = DEFAULT_MONSTER_HEALTH;
  float monster_velocity = DEFAULT_MONSTER_VELOCITY;
  sf::Texture &texture = assassin_t;
  if (roomIndex_ + 1 == rooms_.size()) {
    monster_number = 1;
    damage = BOSS_MONSTER_DAMAGE;
    monster_health = BOSS_MONSTER_HEALTH;
    monster_velocity = BOSS_MONSTER_VELOCITY;
    texture = boss_t;
  }
  for (int _ = 0; _ < monster_number; _++) {
    std::string type = "random type later ig";
    std::string name = "random name later ig";
    auto pos = room_.RandomPos(CREATURE_SIZE);
    res.push_back(new Monster(type, name, monster_health, monster_velocity,
                              pos, window_, room_, (int) damage, texture));
  }
}

int Player::GetRoomIndex() const {
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
  if (!monsters.empty() && help::close(monsters[ind]->GetPosition(), GetPosition(), PLAYER_ATTACK_RADIUS)) {
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
  if (ind < potionPositions.size() && help::len(potionPositions[ind] - position_) <= PLAYER_ATTACK_RADIUS) {
    potionPositions.erase(potionPositions.begin() + ind);
    inventory_.AddPotion(HealthPotion(), 1);
  }
}
void Player::SpawnPotion(std::vector<sf::Vector2f> &pos) {
  // spawns with probability 1/POTION_SPAWN_CHANCE
  if (!RandomEvent(POTION_SPAWN_PROBABILITY)) return; // spawns just one for now, but can be easily changed to spawn more
  pos.push_back(room_.RandomPos(ITEM_SIZE));
}

void Player::UpdateRoomIndex() {
  Room tmp = room_;
  roomIndex_ = int(std::find_if(rooms_.begin(),
                                rooms_.end(),
                                [tmp](const Room &b) { return tmp.GetId() == b.GetId(); })
                       - rooms_.begin());
}