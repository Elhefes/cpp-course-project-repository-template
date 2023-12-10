#include "gameOverScreen.hpp"

void GameOverScreen::Render(sf::RenderWindow &window,
                            sf::Font &font,
                            std::string text,
                            sf::Color textColor,
                            sf::Color buttonColor) {
  sf::Text winText = CreateText(font, text, textColor, window, VERDICT_CHARACTER_SIZE);
  sf::Text buttonText = CreateText(font, "Play Again", sf::Color::White, window, PLAY_AGAIN_CHARACTER_SIZE);
  playAgainButton_ = CreatePlayAgainButton(window, buttonText, buttonColor);
  buttonText.setPosition(playAgainButton_.getPosition());
  buttonText.setOrigin(sf::Vector2f(buttonText.getLocalBounds().width / 2.0f,
                                    buttonText.getLocalBounds().height / 2.0f));
  buttonText.setScale(sf::Vector2f(BUTTON_SCALE, BUTTON_SCALE));

  DrawElements(window, winText, playAgainButton_, buttonText);
  window.display();
}

sf::Text GameOverScreen::CreateText(sf::Font &font,
                                    const std::string &text,
                                    sf::Color textColor,
                                    sf::RenderWindow &window,
                                    unsigned int characterSize) {
  sf::Text newText(font);
  newText.setString(text);
  newText.setCharacterSize(characterSize);
  newText.setFillColor(textColor);
  sf::FloatRect textRect = newText.getLocalBounds();
  newText.setOrigin(sf::Vector2f(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f));
  newText.setPosition(window.getView().getCenter());
  newText.setScale(sf::Vector2f(NEW_TEXT_SCALE, NEW_TEXT_SCALE));
  return newText;
}

sf::RectangleShape GameOverScreen::CreatePlayAgainButton(sf::RenderWindow &window,
                                                         sf::Text &buttonText,
                                                         sf::Color buttonColor) {
  sf::RectangleShape buttonShape(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
  buttonShape.setFillColor(buttonColor);
  sf::FloatRect rect = buttonShape.getLocalBounds();
  buttonShape.setOrigin(sf::Vector2f(rect.width / 2.0f, rect.height / 2.0f));
  buttonShape.setPosition(sf::Vector2(window.getView().getCenter().x,
                                      buttonText.getPosition().y + rect.height * 0.03f));
  buttonShape.setScale(sf::Vector2f(BUTTON_SCALE, BUTTON_SCALE));
  return buttonShape;
}

void GameOverScreen::DrawElements(sf::RenderWindow &window,
                                  sf::Text &winText,
                                  sf::RectangleShape &playAgainButton,
                                  sf::Text &buttonText) {
  window.clear();
  window.draw(winText);
  window.draw(playAgainButton);
  window.draw(buttonText);
}

sf::RectangleShape GameOverScreen::GetPlayAgainButton() {
  return playAgainButton_;
}