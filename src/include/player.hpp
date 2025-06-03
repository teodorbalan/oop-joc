#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player {
  private:
    float maxHealth = 100.f;
    float currentHealth = 100.f;
    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBarFront;

    sf::RectangleShape hitbox;
    std::optional<sf::Sprite> sprite;
    std::vector<sf::Texture> textures;
    float speed = 200.f;
    float animationTimer = 0.f;
    int currentFrame = 0;
    static constexpr int tileSize = 50;
    int direction = 0; // 0-down, 1-left, 2-right, 3-up

  public:
    Player();
    void changeHealth(float amount);
    void drawUI(sf::RenderWindow& window) const;
    float getHealth() const;


    void handleInput(float deltaTime, const std::vector<std::vector<int>>& map);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
    const sf::RectangleShape& getShape() const;
    void loadTextures();
    void updateAnimation(float deltaTime);
    bool canMoveTo(sf::Vector2f position, const std::vector<std::vector<int>>& map);
};
