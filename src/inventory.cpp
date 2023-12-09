#include "inventory.hpp"

template<typename T>
float Inventory::DrawItems(std::vector<T> items,
                           const sf::Texture &t,
                           float x,
                           float y,
                           sf::RenderWindow &window,
                           bool itemInUse) {
  for (const auto &item : items) {
    // Draws the circles
    sf::CircleShape circle(0.5f);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(0.1f);
    if (itemInUse) {
      circle.setOutlineColor(sf::Color::Red);
    } else {
      circle.setOutlineColor(sf::Color::Blue);
    }
    sf::Vector2f center = window.getView().getCenter();
    circle.setPosition(sf::Vector2f(x, y));
    window.draw(circle);

    // Draws the items inside the circles
    sf::Vector2f circleCenter(circle.getPosition());
    Item::Draw(window, circleCenter, 2 * circle.getRadius(), t);

    // if the item is a potion, show quantity
    if (!item.IsSword()) {
      sf::Text quantityText(font);
      quantityText.setString(std::to_string(counter_[item.GetName()]));
      quantityText.setFillColor(sf::Color::White);
      quantityText.setScale(sf::Vector2f(circle.getRadius() / 10, circle.getRadius() / 20));
      quantityText.setPosition(sf::Vector2f(circleCenter.x + circle.getRadius() * 2,
                                            circleCenter.y - circle.getRadius() / 2));
      window.draw(quantityText);
    }

    x += 1.5f;
  }
  return x;
}
int Inventory::GetSize() {
  return swords_.size() + potions_.size();
}
void Inventory::Draw(sf::RenderWindow &window, int itemInUse) {
  sf::Vector2f center = window.getView().getCenter();
  float x = center.x - window.getView().getSize().x / 2 + 0.5;
  float y = center.y - window.getView().getSize().y / 2 + 0.5;

  if (IsSword(itemInUse)) {
    x = DrawItems(swords_, sword_inv_t, x, y, window, true);
    DrawItems(potions_, potion_inv_t, x, y, window, false);
  } else {
    x = DrawItems(swords_, sword_inv_t, x, y, window, false);
    DrawItems(potions_, potion_inv_t, x, y, window, true);
  }

  // assumes that there is only one health potion and sword for now i guess as all the textures are same
}
Sword Inventory::GetSword(int index) {
  // assumes that isSword_[index] is true
  // this dumb implementation assumes that player do not drop swords_
  return swords_[isSword_[index].second];
}
HealthPotion Inventory::GetPotion(int index) {
  return potions_[isSword_[index].second];
}
int Inventory::GetHealingAmount(int index) {
  if (isSword_[index].second) return 0;
  HealthPotion potion = GetPotion(index);
  if (counter_[potion.GetName()] > 0) {
    counter_[potion.GetName()] -= 1;
    return potion.GetHpRestored();
  } else {
    return 0;
  }
}
