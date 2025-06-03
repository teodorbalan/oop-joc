#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include "ResourceManager.hpp"

class Button {
  private:
    sf::RectangleShape shape;
    std::optional<sf::Text> labels;
    sf::Font font = ResourceManager::getFont();
    float margin = 20.f;

  public:
    Button(const std::string& text, unsigned int charSize);

    void setPosition(sf::Vector2f pos);
    // void setFont(const std::string& fontPath);
    void setTextColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setHoverColor(sf::Color hover);
    void update(const sf::RenderWindow& window);
    bool isHovered(const sf::RenderWindow& window) const;
    bool isClicked(const sf::RenderWindow& window) const;

    void draw(sf::RenderWindow& window);
};
