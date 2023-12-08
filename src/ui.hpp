#include <SFML/Graphics.hpp>

class UIManager {
public:
    void renderWinningScreen(sf::RenderWindow& window, sf::Font& font);
    sf::RectangleShape getPlayAgainButton();
};