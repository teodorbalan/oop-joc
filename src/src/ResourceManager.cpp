#include "ResourceManager.hpp"

void ResourceManager::load() {
  if (!font.openFromFile("./assets/fonts/PoiretOne-Regular.ttf")) {
    throw std::runtime_error("Failed to load font");
  }
}

const sf::Font& ResourceManager::getFont() {
  return font;
}



