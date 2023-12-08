#include <SFML/Graphics.hpp>

/**
 * @brief Class for managing the game over screen.
 */
class GameOverScreen {
public:
    /**
     * @brief Renders the game over screen.
     * @param window The render window.
     * @param font The font to use for text rendering.
     * @param text The main text to display.
     * @param textColor The color of the main text.
     * @param buttonColor The color of the play again button.
     */
    void render(sf::RenderWindow& window, sf::Font& font, std::string text, sf::Color textColor, sf::Color buttonColor);

    /**
     * @brief Gets the play again button shape.
     * @return The play again button as an SFML RectangleShape.
     */
    sf::RectangleShape getPlayAgainButton();

private:
    sf::RectangleShape playAgainButton; /**< The play again button. */

    /**
     * @brief Creates text with specified properties.
     * @param font The font to use for the text.
     * @param text The string content of the text.
     * @param textColor The color of the text.
     * @param window The render window.
     * @param characterSize The character size of the text.
     * @return The created SFML Text object.
     */
    sf::Text createText(sf::Font& font, std::string text, sf::Color textColor, sf::RenderWindow& window, unsigned int characterSize);

    /**
     * @brief Creates the play again button with specified properties.
     * @param window The render window.
     * @param buttonText The text displayed on the button.
     * @param buttonColor The color of the button.
     * @return The created SFML RectangleShape object representing the button.
     */
    sf::RectangleShape createPlayAgainButton(sf::RenderWindow& window, sf::Text& buttonText, sf::Color buttonColor);

    /**
     * @brief Draws elements onto the render window.
     * @param window The render window to draw on.
     * @param winText The text to be drawn.
     * @param playAgainButton The play again button to be drawn.
     * @param buttonText The text on the play again button to be drawn.
     */
    void drawElements(sf::RenderWindow& window, sf::Text& winText, sf::RectangleShape& playAgainButton, sf::Text& buttonText);
};