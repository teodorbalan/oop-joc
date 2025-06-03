#include "Button.hpp"
#include <iostream>

Button::Button(const std::string& text, unsigned int charSize) {

  sf::Text label(font);
  label.setString(text);
  label.setCharacterSize(charSize);
  label.setFillColor(sf::Color::White);

  sf::FloatRect textBounds = label.getLocalBounds();

  float buttonWidth = textBounds.size.x + margin * 2.f;
  float buttonHeight = textBounds.size.y + margin * 2.f;

  shape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
  shape.setFillColor(sf::Color::Transparent);
  shape.setOutlineColor(sf::Color::White);
  shape.setOutlineThickness(2.f);

  shape.setOrigin({buttonWidth / 2.f, buttonHeight / 2.f});
  label.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                  textBounds.position.y + textBounds.size.y / 2.f});

  labels.emplace(label);
}

void Button::setPosition(sf::Vector2f pos) {
  shape.setPosition(pos);
  labels->setPosition(pos);
}

// void Button::setFont(const std::string& fontPath) {
//   font.loadFromFile(fontPath);
//   label.setFont(font);
// }

void Button::setTextColor(sf::Color color) {
  labels->setFillColor(color);
}

void Button::setOutlineColor(sf::Color color) {
  shape.setOutlineColor(color);
}

void Button::update(const sf::RenderWindow& window) {
  if(isHovered(window))
    shape.setOutlineColor(sf::Color::Red);
  else
    shape.setOutlineColor(sf::Color::White);
}

bool Button::isHovered(const sf::RenderWindow& window) const {
  sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
  return shape.getGlobalBounds().contains(mousePos);
}

bool Button::isClicked(const sf::RenderWindow& window) const {
  return isHovered(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Button::draw(sf::RenderWindow& window) {
  window.draw(shape);
  window.draw(*labels);
}
