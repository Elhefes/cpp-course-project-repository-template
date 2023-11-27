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
                   const std::vector<Item> &inventory)
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

const std::string &Creature::GetDescription() const {
  return description_;
}

int Creature::TakeHit(int base_damage, const Creature &c2) {
  // maybe calculate damage somehow (defense stats?)
  int damageDealt = std::min(base_damage, health_);
  this->TakeDamage_(damageDealt);
  logger_ << c2.GetDescription() << " dealt " << damageDealt << " damage to " << GetDescription() << "!" << std::endl;
  return damageDealt;
}

void Creature::Draw() {
  auto relativePos = position_;
  sprite_.setPosition(relativePos); // change some stuff when get actual sprite
  if (!IsAlive()) sprite_.setFillColor(sf::Color::Cyan);
  window_.draw(sprite_);
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
  const int OFFSET = 10; // sfml specifics ig
  auto newPos = position_ + velocity_;
  // check bounds
  int width = room_.width;
  int height = room_.width;
  // won't work once we replace the sprite tho :((
  float xlim = (float) (room_.x + width) - 2 * sprite_.getRadius();
  float ylim = (float) (room_.y + height) - 2 * sprite_.getRadius() - OFFSET;
  newPos.x = bound(newPos.x, (float) room_.x, xlim);
  newPos.y = bound(newPos.y, (float) room_.y, ylim);
  if (newPos.x == xlim || newPos.x == room_.x) velocity_.x *= -1;
  if (newPos.y == ylim || newPos.y == room_.y) velocity_.y *= -1;
  SetPosition(newPos); // doing it via setPos so the camera gets updated too

  sprite_.setPosition(position_);
}

const std::vector<Item> &Creature::GetInventory() const {
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
void Creature::SetHealth(int health) {
  health_ = std::min(health, maxHealth_);
}
void Creature::SetSprite(const sf::CircleShape &sprite) {
  sprite_ = sprite;
}
const Room &Creature::GetRoom() const {
  return room_;
}
int Creature::Attack(Creature &c2, const Item *item) {
  if (item == nullptr) {
    return c2.TakeHit(base_damage_, *this);
  }
  // do some calculations based on item's nature
  return c2.TakeHit(base_damage_ + 1, *this);

}
void Creature::SetPosition(const sf::Vector2<float> &position) {
  position_ = position;
}
void Creature::SetRoom(Room &room) {
  room_ = room;
}
const float Creature::GetMaxVelocity() const {
  return maxVelocity_;
}

