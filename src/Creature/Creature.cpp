#include "Creature.hpp"
#include "iostream"

Creature::Creature(const std::string &type,
                   const std::string &name,
                   int maxHealth,
                   float maxVelocity,
                   const sf::Vector2<float> &initialPos,
                   sf::RenderWindow &window,
                   const Room &room,
                   int base_damage,
                   std::ostream &logger,
                   const sf::CircleShape &sprite,
                   const Inventory &inventory)
    : type_(type),
      name_(name),
      maxHealth_(maxHealth),
      health_(maxHealth_),
      maxVelocity_(maxVelocity),
      window_(window),
      room_(room),
      base_damage_(base_damage),
      logger_(logger),
      inventory_(inventory),
      position_(initialPos),
      sprite_(sprite) {
  description_ = "Creature \"" + type + " named " + name + "\"";
}

const float PI = 3.14159265;

const std::string &Creature::GetDescription() const {
  return description_;
}

int Creature::TakeHit(float base_damage, const Creature &c2) {
  // maybe calculate damage somehow (defense stats?)
  float damageDealt = std::min(base_damage, (float) health_);
  this->TakeDamage_(damageDealt);
  logger_ << c2.GetDescription() << " dealt " << damageDealt << " damage to " << GetDescription() << "!" << std::endl;
  return damageDealt;
}

const std::string &Creature::GetType() const {
  return type_;
}

void Creature::Draw() { // TODO: set all those values on create
  creatureRect.setSize(sf::Vector2f(1.0f, 1.0f));
  creatureRect.setOrigin(sf::Vector2f(0.5f, 0.5f));

  creatureRect.setOutlineColor(sf::Color::Red);
  creatureRect.setOutlineThickness(0.05f);
  sf::CircleShape tmp(0.1);
  tmp.setFillColor(sf::Color::Blue);
  tmp.setPosition(position_ - sf::Vector2f(0.5f, 0.5f));
  window_.draw(tmp);
  tmp.setPosition(position_ + sf::Vector2f(0.5f, 0.5f));
  window_.draw(tmp);
  window_.draw(creatureRect);
  sf::RectangleShape tmp2(sf::Vector2f(0.1, room_.height));
  tmp2.setPosition(sf::Vector2f(room_.x, room_.y));
  window_.draw(tmp2);

  if (GetType() == "Hooman") {
    creatureRect.setTexture(&player_t);
  } else {
    creatureRect.setTexture(&assassin_t);
  }
  creatureRect.setPosition(position_);
  if (!IsAlive()) creatureRect.setFillColor(sf::Color::Red);
  window_.draw(creatureRect);
//  auto r = sprite_.getRadius();
//  sf::Vertex line[] =
//      {
//          sf::Vertex(relativePos),
//          sf::Vertex(relativePos + sf::Vector2f(2 * r, 0)),
//          sf::Vertex(relativePos + sf::Vector2f(2 * r, 2 * r)),
//          sf::Vertex(relativePos + sf::Vector2f(0, 2 * r))
//      };
//  helper.setPosition(relativePos);
//  window_.draw(line, 4, sf::Lines);
//  sf::Vertex line[] = {
//      sf::Vertex(sf::Vector2f(room_.x - camera.position.x, room_.y - camera.position.y - 2 * r)),
//      sf::Vertex(sf::Vector2f(room_.x - camera.position.x + room_.width, room_.y - 2 * r - camera.position.y)),
//  };
//  window_.draw(line, 2, sf::Lines);
}

void Creature::Update() {
  if (!IsAlive()) return;
  UpdatePosition();
  UpdateRotation();
}

const Inventory &Creature::GetInventory() const {
  return inventory_;
}
const sf::Vector2<float> &Creature::GetPosition() const {
  return position_;
}
const sf::Vector2<float> &Creature::GetVelocity() const {
  return velocity_;
}

template<typename T>
int sign(T x) {
  if (x > 0) return 1;
  else if (x < 0) return -1;
  else return 0;
}

template<typename T>
T limitModule(T x, T limit) {
  if (std::abs(x) > limit) {
    x = sign(x) * limit;
  }
  return x;
}
void Creature::SetVelocity(const sf::Vector2<float> &newVelocity) {
  SetVelocityX(newVelocity.x);
  SetVelocityY(newVelocity.y);
}

void Creature::SetVelocityX(float nvx) { velocity_.x = limitModule(nvx, maxVelocity_); }
void Creature::SetVelocityY(float nvy) { velocity_.y = limitModule(nvy, maxVelocity_); }
void Creature::SetHealth(float health) {
  health_ = std::min(health, maxHealth_);
}
void Creature::SetSprite(const sf::CircleShape &sprite) {
  sprite_ = sprite;
}
const Room &Creature::GetRoom() const {
  return room_;
}

Inventory &Creature::GetInventory() {
  return inventory_;
}

int Creature::Attack(Creature &c2, const Sword &sword) const {
  if (sword.GetName().empty()) { // no sword was passed
    return c2.TakeHit(base_damage_, *this);
  }
  // do some calculations based on item's nature
  float damage = base_damage_ * sword.GetMultiplier();
  return c2.TakeHit(damage, *this);

}
void Creature::SetPosition(const sf::Vector2<float> &position) {
  position_ = position;
}
void Creature::SetRoom(Room &room) {
  room_ = room;
}
float Creature::GetMaxVelocity() const {
  return maxVelocity_;
}
std::vector<Room> Creature::GetAvailableRooms() {
  // default behaviour: only my room is available
  // will be overriden by player class
  // TODO: move this to documentation
  return {room_};
}
void Creature::UpdatePosition() {
  // assumes that creature is alive
  sf::Vector2f newPos = position_ + velocity_;
  std::vector<Room> rooms = GetAvailableRooms();
  for (auto &r : rooms) {
    float sz = std::max(creatureRect.getSize().x, creatureRect.getSize().y);
    auto [isInside, xMul, yMul, boundedPos] = r.isInside(newPos, sz);
    if (isInside) {
      position_ = boundedPos;
      velocity_.x *= xMul;
      velocity_.y *= yMul;
      SetRoom(r);
      return;
    }
  }
}
void Creature::UpdateRotation() {
  auto [dx, dy] = GetFacingDirection();
  TurnToDirection(dx, dy);
}

sf::Vector2f Creature::GetFacingDirection() {
  // will be overriden by player class
  return velocity_;
}

void Creature::TurnToDirection(float dx, float dy) {
  float rotation = atan2f(dy, dx);
  creatureRect.setRotation(sf::radians(rotation - M_PI_2f32));
}

