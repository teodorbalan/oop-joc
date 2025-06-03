#include "MenuScene.hpp"
#include "ResourceManager.hpp"
#include <iostream>
#include <SFML/Audio.hpp>


MenuScene::MenuScene() 
: startButton("Start Game", 20) 
{
  startButton.setPosition({1280.f / 2.f, 720.f / 2.f});
  if (!backgroundTexture.loadFromFile("./assets/photos/menu.jpg")) {
    std::cerr << "Failed to load menu background.\n";
  } else {
    backgroundSprite.emplace(backgroundTexture);
    sf::Vector2u textureSize = backgroundTexture.getSize();

    sf::Vector2f windowSize(1280.f, 720.f); 

    float scaleX = windowSize.x / textureSize.x;
    float scaleY = windowSize.y / textureSize.y;

    backgroundSprite->setScale({scaleX, scaleY});  
    }

    sf::Text Text(ResourceManager::getFont());
    Text.setCharacterSize(24); 
    Text.setFillColor(sf::Color::White);
    Text.setPosition({10.f, 10.f}); 
    fpsText.emplace(Text);

    if(!backgroundMusic.openFromFile("./assets/audio/menuAudio.mp3")) {
    } else {
      backgroundMusic.setLooping(true); 
      backgroundMusic.setVolume(50.f); 
      backgroundMusic.play();
    }

    titleText = sf::Text(ResourceManager::getFont());
    titleText->setCharacterSize(48);
    titleText->setFillColor(sf::Color::Red);
    titleText->setString("Incepe Sesiunea!");
    titleText->setPosition({1280.f / 2.f, 100.f}); 
    titleText->setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleText->setOrigin({titleText->getLocalBounds().size.x / 2.f, 0.f}); 
}

std::optional<std::string> MenuScene::handleEvents(sf::RenderWindow& window) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>())
      window.close();
    else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        window.close();
      else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
        return "game"; 
    } else if(const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if(startButton.isClicked(window)) {
          backgroundMusic.stop();
          std::cout << "Start button clicked\n";
          return "game"; 
        }
      }
  }
  return std::nullopt;
}

void MenuScene::update(float deltaTime) {
  frameCount++;
  elapsedTime += fpsClock.restart().asSeconds();

  if(elapsedTime >= 1.0f) {
    float fps = frameCount / elapsedTime;
    fpsText->setString("FPS: " + std::to_string(static_cast<int>(fps)));
    frameCount = 0;
    elapsedTime = 0.0f;
  }
}

void MenuScene::render(sf::RenderWindow& window) {
  window.clear();  

  window.draw(*backgroundSprite);
  window.draw(*fpsText);
  startButton.update(window);
  startButton.draw(window);
  window.draw(*titleText);


  window.display();
}

