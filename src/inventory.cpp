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
    sf::CircleShape circle(ITEM_CIRCLE_RADIUS);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(ITEM_CIRCLE_OUTLINE_THICKNESS);
    if (itemInUse) {
      circle.setOutlineColor(ITEM_IN_USE_COLOR);
    } else {
      circle.setOutlineColor(ITEM_NOT_IN_USE_COLOR);
    }
    sf::Vector2f center = window.getView().getCenter();
    circle.setPosition(sf::Vector2f(x, y));
    window.draw(circle);

    // Draws the items inside the circles
    sf::Vector2f circleCenter(circle.getPosition());
    Item::Draw(window, circleCenter, ITEM_SIZE, t);

    // if the item is a potion, show quantity
    if (!item.IsSword()) {
      sf::Text quantityText(font);
      quantityText.setString(std::to_string(counter_[item.GetName()]));
      quantityText.setFillColor(sf::Color::White);
      quantityText.setScale(sf::Vector2f(circle.getRadius() / QUANTITY_TEXT_SCALE_X,
                                         circle.getRadius() / QUANTITY_TEXT_SCALE_Y));
      quantityText.setPosition(sf::Vector2f(circleCenter.x + circle.getRadius() * 2,
                                            circleCenter.y - circle.getRadius() / 2));
      window.draw(quantityText);
    }

    x += 3 * ITEM_CIRCLE_RADIUS;
  }
  return x;
}
int Inventory::GetSize() {
  return swords_.size() + potions_.size();
}
void Inventory::Draw(sf::RenderWindow &window, int itemInUse) {
  sf::Vector2f center = window.getView().getCenter();
  float x = center.x - window.getView().getSize().x / 2 + ITEM_CIRCLE_RADIUS;
  float y = center.y - window.getView().getSize().y / 2 + ITEM_CIRCLE_RADIUS;

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
