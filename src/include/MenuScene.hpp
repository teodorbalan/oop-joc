#pragma once
#include "Scene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include "button.hpp"

class MenuScene : public Scene {
  private:
    sf::Music backgroundMusic;
    sf::Texture backgroundTexture;
    std::optional<sf::Sprite> backgroundSprite;
    std::optional<sf::Text> fpsText;
    Button startButton;
    sf::Clock fpsClock;
    int frameCount = 0;
    float elapsedTime = 0.0f;
    std::optional<sf::Text> titleText;
    

  public:
    MenuScene();
    std::optional<std::string> handleEvents(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
