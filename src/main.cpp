#include <iostream>
#include <SFML/Graphics.hpp>

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler");
    window.setFramerateLimit(60);

    while (window.isOpen()) {

    }

	std::cout << "Hello World" << std::endl;
	return 0;
}