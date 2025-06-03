#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>

class ResourceManager {
public:

  static void load();

  static const sf::Font& getFont();

private:
  inline static sf::Font font;

  ResourceManager() = delete;
};
