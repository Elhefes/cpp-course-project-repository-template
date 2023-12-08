#include "ui.hpp"

void UIManager::renderWinningScreen(sf::RenderWindow& window, sf::Font& font) {
    /*
  sf::Text winText(font);
  winText.setFont(font);
  winText.setString("Congratulations! You won!");
  winText.setCharacterSize(100);
  winText.setFillColor(sf::Color::Green);
  sf::FloatRect textRect = winText.getLocalBounds();
  winText.setOrigin(sf::Vector2(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f));
  winText.setPosition(window.getView().getCenter());
  winText.setScale(sf::Vector2f(0.01f, 0.01f));

  // Create a "Play Again" button aligned just under the Congratulations text
  playAgainButton = sf::RectangleShape(sf::Vector2f(200, 50));
  playAgainButton.setFillColor(sf::Color::Blue);
  sf::FloatRect rect = playAgainButton.getLocalBounds();
  playAgainButton.setOrigin(sf::Vector2(rect.width / 2.0f, rect.height / 2.0f));
  playAgainButton.setPosition(sf::Vector2(window.getView().getCenter().x, winText.getPosition().y + textRect.height * 0.02f));
  playAgainButton.setScale(sf::Vector2f(0.02f, 0.02f));

  sf::Text buttonText(font);
  buttonText.setFont(font);
  buttonText.setString("Play Again");
  buttonText.setCharacterSize(24);
  buttonText.setFillColor(sf::Color::White);
  sf::FloatRect buttonRect = buttonText.getLocalBounds();
  buttonText.setOrigin(sf::Vector2(buttonRect.left + buttonRect.width / 2.0f, buttonRect.top + buttonRect.height / 2.0f));
  buttonText.setPosition(playAgainButton.getPosition());
  buttonText.setScale(sf::Vector2f(0.02f, 0.02f));

  window.clear();
  window.draw(winText);
  window.draw(playAgainButton);
  window.draw(buttonText);
  window.display();
  */
}

sf::RectangleShape UIManager::getPlayAgainButton() {
    sf::RectangleShape playAgainButton(sf::Vector2f(200, 50));
    return playAgainButton;
}