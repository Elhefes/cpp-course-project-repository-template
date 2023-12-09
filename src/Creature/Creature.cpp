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
                   sf::Texture &t,
                   std::ostream &logger,
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
      texture_(t) {
  description_ = "Creature \"" + type + " named " + name + "\"";
  creatureRect_.setSize(sf::Vector2f(1.0f, 1.0f));
  creatureRect_.setOrigin(sf::Vector2f(0.5f, 0.5f));
}

const std::string &Creature::GetDescription() const {
  return description_;
}

float Creature::TakeHit(float base_damage, const Creature &c2) {
  // maybe calculate damage somehow (defense stats?)
  float damageDealt = std::min(base_damage, (float) health_);
  this->TakeDamage_(damageDealt);
  logger_ << c2.GetDescription() << " dealt " << damageDealt << " damage to " << GetDescription() << "!" << std::endl;
  return damageDealt;
}

void Creature::Draw() {
  creatureRect_.setTexture(&texture_);
  creatureRect_.setPosition(position_);
  if (!IsAlive()) creatureRect_.setFillColor(sf::Color::Red);
  window_.draw(creatureRect_);
}

void Creature::Update() {
  if (!IsAlive()) return;
  UpdatePosition();
  UpdateRotation();
}

const sf::Vector2<float> &Creature::GetPosition() const {
  return position_;
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

void Creature::SetTexture(const sf::Texture &t) {
  texture_ = t;
  creatureRect_.setTexture(&t);
}

const Room &Creature::GetRoom() const {
  return room_;
}

Inventory &Creature::GetInventory() {
  return inventory_;
}

float Creature::Attack(Creature &c2, const Sword &sword) const {
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

std::vector<Room> Creature::GetAvailableRooms() {
  // default behaviour: only my room is available
  // will be overriden by player class
  return {room_};
}

void Creature::UpdatePosition() {
  // assumes that creature is alive
  sf::Vector2f newPos = position_ + velocity_;
  std::vector<Room> rooms = GetAvailableRooms();
  for (auto &r : rooms) {
    float sz = std::max(creatureRect_.getSize().x, creatureRect_.getSize().y);
    auto [isInside, xMul, yMul, boundedPos] = r.IsInside(newPos, sz);
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
  creatureRect_.setRotation(sf::radians(rotation - M_PI_2f32));
}

void Creature::DrawHealthBar(sf::RenderWindow &window) {
  float barWidth = 0.3f;
  sf::RectangleShape healthBar(sf::Vector2f(barWidth, 0.2f));
  healthBar.setFillColor(sf::Color::Green);
  healthBar.setPosition(sf::Vector2f(position_.x - barWidth * 2, position_.y - 0.8f));

  float healthRatio = health_ / maxHealth_;
  healthBar.setSize(sf::Vector2f(healthRatio, 0.2f));

  sf::Color maxHealthColor = sf::Color::Green;
  sf::Color minHealthColor = sf::Color::Red;

  sf::Color barColor = sf::Color(
      float(minHealthColor.r + (maxHealthColor.r - minHealthColor.r) * healthRatio),
      float(minHealthColor.g + (maxHealthColor.g - minHealthColor.g) * healthRatio),
      float(minHealthColor.b + (maxHealthColor.b - minHealthColor.b) * healthRatio)
  );

  healthBar.setFillColor(barColor);
  window.draw(healthBar);
}

void Creature::TakeDamage_(float damage) { health_ = std::max(0.f, health_ - damage); }
