#include <iostream>
#include <SFML/Graphics.hpp>
#include "Creature/Creature.hpp"
#include "Creature/Assassin.hpp"

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
  Creature dragon("Dragon", "Willy", 1000, {10, 10}, window, std::cout, shape1);
  Assassin assassin("Ben", {500, 500}, window, std::cout, shape2);
  // Creature testing end

  while (window.isOpen()) {
    window.clear();
    // Creature testing
    dragon.Draw();
    assassin.Draw();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dragon.SetVelocityX(5);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dragon.SetVelocityX(-5);
    else dragon.SetVelocity({0, 0});
    dragon.Update();
    assassin.Update();
    // Creature testing end
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::K) {
          dragon.TakeHit(125, assassin);
        } else if (event.key.code == sf::Keyboard::LShift) {
          assassin.Special();
        }

      }
    }
    window.display();
  }

  return 0;
}