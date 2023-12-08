#include <SFML/Graphics.hpp>

class GameOverScreen {
public:
    void render(sf::RenderWindow& window, sf::Font& font, std::string text, sf::Color textColor, sf::Color buttonColor);
    sf::RectangleShape getPlayAgainButton();
private:
    sf::RectangleShape playAgainButton;

    sf::Text createText(sf::Font& font, std::string text, sf::Color textColor, sf::RenderWindow& window, unsigned int characterSize);
    sf::RectangleShape createPlayAgainButton(sf::RenderWindow& window, sf::Text& buttonText, sf::Color buttonColor);
    void drawElements(sf::RenderWindow& window, sf::Text& winText, sf::RectangleShape& playAgainButton, sf::Text& buttonText);
};