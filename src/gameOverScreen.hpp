#include <SFML/Graphics.hpp>

class GameOverScreen {
public:
    void render(sf::RenderWindow& window, sf::Font& font, std::string text, sf::Color textColor);
    sf::RectangleShape getPlayAgainButton();
private:
    sf::RectangleShape playAgainButton;
};