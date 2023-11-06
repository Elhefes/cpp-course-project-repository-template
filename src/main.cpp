#include <iostream>
#include <SFML/Graphics.hpp>
#include "Creature/Creature.hpp"

int main() {
  std::cout << "Hello World" << std::endl;
  sf::Vector2u windowSize(800u, 600u);
  const uint WINDOW_WIDTH = 800u, WINDOW_HEIGHT = 600u;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dungeon Crawler");
  window.setFramerateLimit(60);

  // Creature testing
  sf::CircleShape shape1(50);
  shape1.setFillColor(sf::Color(123, 121, 200));
  sf::CircleShape shape2(50);
  shape2.setFillColor(sf::Color(239, 13, 214));
  Creature c1("Dragon", "Willy", 1000, {10, 10}, shape1);
  Creature c2("Hooman", "Ben", 50, {90, 90}, shape2);
  // Creature testing end

  while (window.isOpen()) {
    window.clear();
    // Creature testing
    c1.Draw(window);
    c2.Draw(window);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) c1.SetVelocityX(5);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) c1.SetVelocity({-5, -5});
    else c1.SetVelocity({0, 0});
    c1.Update(window);
    c2.Update(window);
    // Creature testing end
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.display();
  }

  return 0;
}