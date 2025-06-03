#include "SceneManager.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"

SceneManager::SceneManager()
  : window(sf::VideoMode({1280, 720}), "My Game") {
  switchScene(std::make_shared<MenuScene>());
  window.setVerticalSyncEnabled(true);
}

void SceneManager::switchScene(std::shared_ptr<Scene> newScene) {
  currentScene = std::move(newScene);
}

void SceneManager::run() {
  sf::Clock clock;

  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();

    if (currentScene) {
      auto requestedScene = currentScene->handleEvents(window);
      
      if (requestedScene.has_value()) {
        const std::string& sceneName = *requestedScene;

        if (sceneName == "game") {
          switchScene(std::make_shared<GameScene>());
        }
        else if (sceneName == "menu") {
          switchScene(std::make_shared<MenuScene>());
        }
      }

      currentScene->update(deltaTime);
      currentScene->render(window);
    }
  }
}
