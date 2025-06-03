#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include "Player.hpp"
#include "Enemy.hpp"
#include <SFML/Audio.hpp>



class GameScene : public Scene {
  private:
    Player player;
    sf::View view;
    static constexpr int tileSize = 50;
    static constexpr int mapWidth = 100;
    static constexpr int mapHeight = 200;
    std::vector<Enemy> enemies;
    int level = 0;
    sf::Music backgroundMusic;
    sf::Music badGradeMusic;
    sf::Music goodGradeMusic;
    sf::Music nextLevelMusic;
    sf::Music failedSessionMusic;

    std::vector<std::vector<int>> map; // 0 = tile, 2 = wall, 3 = door
    sf::Texture floorTexture;
    sf::RectangleShape floor;
    sf::Texture wallTexture;
    sf::RectangleShape wall;
    sf::Texture doorTexture;
    sf::RectangleShape door;

    sf::Texture deadTexture;
    std::optional<sf::Sprite> deadSprite;
    std::optional<sf::Text> deadText;

    float doorCooldown = 0.f; 

    

  public:
    GameScene();
    std::optional<std::string> handleEvents(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void generateEnemyLevel();
    std::vector<sf::Vector2i> floodFillRoom(sf::Vector2i start);
    std::vector<sf::Vector2i> getNeighbors(sf::Vector2i pos);
};
