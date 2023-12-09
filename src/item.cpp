#include "Item.hpp"
void Item::Draw(sf::RenderWindow &window, const sf::Vector2f &pos, float maxSize, const sf::Texture &t) {
  // todo: if i had more time, i would rewrite the item to have texture as a field
  //  and the method would not have been static
  sf::Sprite sprite(t);
  sf::FloatRect itemBounds = sprite.getGlobalBounds();
  float scale = maxSize / std::max(itemBounds.width, itemBounds.height);
  sprite.setScale(sf::Vector2f(scale, scale));
  sprite.setPosition(pos);
  window.draw(sprite);
}
