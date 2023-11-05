#include "Creature.hpp"
#include "iostream"

const std::string &Creature::GetDescription() const {
  return description_;
}

int Creature::TakeHit(int base_damage, const Creature &c2) {
  // maybe calculate damage somehow (defense stats?)
  int damage_dealt = std::min(base_damage, health_);
  this->TakeDamage(damage_dealt);
  std::cout << c2.GetDescription() << " dealt " << damage_dealt << " to " << GetDescription() << "!";
}