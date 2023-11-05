#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    std::cout << "Hello World" << std::endl;
    sf::Vector2u windowSize(800u, 600u);
    const uint WINDOW_WIDTH = 800u, WINDOW_HEIGHT = 600u;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dungeon Crawler");
    window.setFramerateLimit(60);

    while (window.isOpen()) {

    }

    return 0;
}