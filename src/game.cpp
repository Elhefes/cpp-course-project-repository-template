#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

/*
TODO: create some sort of tests here to check whether items, dungeons etc
are working properly as discussed with the project advisor
*/

class Game {
public:
    Game() {
        sf::Vector2u windowSize(800u, 600u);
        window.create(sf::VideoMode(windowSize), "Dungeon Crawler");
        window.setFramerateLimit(60);

        // Initialize the moving object (circle)
        circle.setRadius(20);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(sf::Vector2f(100u, 300u));
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::CircleShape circle;

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle other input events (keyboard, mouse, etc.)
        }
    }

    void update() {
        // Update game objects, handle collisions, implement game logic
        // Update player, enemies, levels, etc.

        // Example: Move the circle to the right
        sf::Vector2f newPosition = circle.getPosition();
        newPosition.x += 1;
        circle.setPosition(newPosition);
    }

    void render() {
        window.clear();
        // Render game objects, backgrounds, UI elements, etc.
        // Render player, enemies, levels, HUD, etc.

        // Render the moving object (circle)
        window.draw(circle);

        window.display();
    }

};