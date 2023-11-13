#include "Creature.hpp"
#include "iostream"

Creature::Creature(const std::string &type,
                   const std::string &name,
                   int maxHealth,
                   const sf::Vector2<float> &initialPos,
                   sf::RenderWindow &window,
                   std::ostream &logger,
                   const sf::CircleShape &sprite_,
                   const std::vector<Item> &inventory)
    : type_(type),
      name_(name),
      maxHealth_(maxHealth),
      health_(maxHealth_),
      window_(window),
      logger_(logger),
      items_(inventory),
      position_(initialPos),
      sprite_(sprite_) {
  description_ = "Creature \"" + type + " named " + name + "\"";
}

const std::string &Creature::GetDescription() const {
  return description_;
}

int Creature::TakeHit(int base_damage, const Creature &c2) {
  // maybe calculate damage somehow (defense stats?)
  int damage_dealt = std::min(base_damage, health_);
  this->TakeDamage_(damage_dealt);
  logger_ << c2.GetDescription() << " dealt " << damage_dealt << " ddamage to " << GetDescription() << "!" << std::endl;
  return damage_dealt;
}

void Creature::Draw() const {
  window_.draw(sprite_);
}

template<typename T>
T bound(T x, T lower, T upper) {
  x = std::max(lower, x);
  x = std::min(x, upper);
  return x;
}

void Creature::Update() {
  position_ += velocity_;
  // check bounds
  auto sz = window_.getSize();
  position_.x = bound(position_.x,
                      (float) 0,
                      (float) sz.x - 2 * sprite_.getRadius()); // won't work once we replace the sprite tho :((
  position_.y = bound(position_.y, (float) 0, (float) sz.y - 2 * sprite_.getRadius());
  sprite_.setPosition(position_); // it is not optimal to set it every frame, but i guess it is negligible
}
