#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include <iostream>

int main() {
  try {
    ResourceManager::load();
  } catch (const std::exception& e) {
    std::cout << e.what() << "\n";
    return 1;
  }
  SceneManager sceneManager;
  sceneManager.run();
  return 0;
}
