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
                   const std::vector<Item> &inventory,
                   std::vector<Room> rooms,
                   std::vector<Room> corridors)
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
      sprite_(sprite),
      rooms_(rooms),
      corridors_(corridors) {
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

void Creature::Update(bool monstersKilled) {
  if (!IsAlive()) return;
  const int OFFSET = 10; // sfml specifics ig
  auto newPos = position_ + velocity_;
  auto newCPos = position_ + velocity_;
  // check bounds
  int width = room_.width;
  int height = room_.height;
  // won't work once we replace the sprite tho :((
  //std::cout << corridors_[0].height << std::endl;
  Room corridor = corridors_[0];
  int index = 0;
  for (int i = 0; i < (rooms_.size() - 1); ++i) {
    if (room_.getId() == rooms_[i].getId()) {
      index = i;
      corridor = corridors_[i];
    }
  }
  using namespace sf;

  FloatRect room1(sf::Vector2f(room_.x, room_.y), sf::Vector2f(room_.width, room_.height));
  FloatRect room2(sf::Vector2f(rooms_[index + 1].x, rooms_[index + 1].y), sf::Vector2f(rooms_[index + 1].width, rooms_[index + 1].height));
  FloatRect corridor1(sf::Vector2f(corridor.x, corridor.y), sf::Vector2f(abs(corridor.width), abs(corridor.height)));

  sf::Vector2f temp = position_;

  position_ = newPos;
  sprite_.setPosition(position_);

  sf::FloatRect playerBounds = sprite_.getGlobalBounds();

  std::optional<sf::FloatRect> r1Intersection = room1.findIntersection(playerBounds);
  std::optional<sf::FloatRect> r2Intersection = room2.findIntersection(playerBounds);
  std::optional<sf::FloatRect> cIntersection = corridor1.findIntersection(playerBounds);

  if (!r1Intersection && !r2Intersection && !cIntersection) {
    position_ = temp;
    sprite_.setPosition(position_);
  }

  if (r2Intersection) {
    room_ = rooms_[index + 1];
  }
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

