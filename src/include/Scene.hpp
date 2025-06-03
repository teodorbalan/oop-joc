#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

class Scene {
  public:
    virtual ~Scene() = default;
    virtual std::optional<std::string> handleEvents(sf::RenderWindow&) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow&) = 0;
};
