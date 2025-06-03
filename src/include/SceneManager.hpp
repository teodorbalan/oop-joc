#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Scene.hpp"

class SceneManager {
  private:
    std::shared_ptr<Scene> currentScene;
    sf::RenderWindow window;

  public:
    SceneManager();
    void run();
    void switchScene(std::shared_ptr<Scene> newScene);
};
