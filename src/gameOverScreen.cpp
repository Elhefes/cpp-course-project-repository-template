#include "gameOverScreen.hpp"

void GameOverScreen::render(sf::RenderWindow& window, sf::Font& font, std::string text, sf::Color textColor, sf::Color buttonColor) {
    sf::Text winText = createText(font, text, textColor, window, 100);
    sf::Text buttonText = createText(font, "Play Again", sf::Color::White, window, 24);
    playAgainButton = createPlayAgainButton(window, buttonText, buttonColor);
    buttonText.setPosition(playAgainButton.getPosition());
    buttonText.setOrigin(sf::Vector2f(buttonText.getLocalBounds().width / 2.0f, buttonText.getLocalBounds().height / 2.0f));
    buttonText.setScale(sf::Vector2f(0.02f, 0.02f));
    
    drawElements(window, winText, playAgainButton, buttonText);
    window.display();
}

sf::Text GameOverScreen::createText(sf::Font& font, std::string text, sf::Color textColor, sf::RenderWindow& window, unsigned int characterSize) {
    sf::Text newText(font);
    newText.setString(text);
    newText.setCharacterSize(characterSize);
    newText.setFillColor(textColor);
    sf::FloatRect textRect = newText.getLocalBounds();
    newText.setOrigin(sf::Vector2f(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f));
    newText.setPosition(window.getView().getCenter());
    newText.setScale(sf::Vector2f(0.01f, 0.01f));
    return newText;
}

sf::RectangleShape GameOverScreen::createPlayAgainButton(sf::RenderWindow& window, sf::Text& buttonText, sf::Color buttonColor) {
    sf::RectangleShape buttonShape(sf::Vector2f(200, 50));
    buttonShape.setFillColor(buttonColor);
    sf::FloatRect rect = buttonShape.getLocalBounds();
    buttonShape.setOrigin(sf::Vector2f(rect.width / 2.0f, rect.height / 2.0f));
    buttonShape.setPosition(sf::Vector2(window.getView().getCenter().x, buttonText.getPosition().y + rect.height * 0.03f));
    buttonShape.setScale(sf::Vector2f(0.02f, 0.02f));
    return buttonShape;
}

void GameOverScreen::drawElements(sf::RenderWindow& window, sf::Text& winText, sf::RectangleShape& playAgainButton, sf::Text& buttonText) {
    window.clear();
    window.draw(winText);
    window.draw(playAgainButton);
    window.draw(buttonText);
}

sf::RectangleShape GameOverScreen::getPlayAgainButton() {
    return playAgainButton;
}