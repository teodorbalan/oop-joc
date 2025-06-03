#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Enemy {
  private:
    sf::RectangleShape hitbox;
    std::optional<sf::Text> numberText;
    float speed = 50.f;
    int number;
    int direction = 0; // 0-down, 1-left, 2-right, 3-up
    float decisionTimer = 0.f;
    int difficulty; 

    sf::Vector2f getDirectionVector() const;
    bool canMoveTo(sf::Vector2f position, const std::vector<std::vector<int>>& map, 
                  const sf::RectangleShape& playerHitbox, 
                  const std::vector<Enemy>& others) const;
    static constexpr int tileSize = 50;

    void moveRandom(float deltaTime, const std::vector<std::vector<int>>& map, 
                    const sf::RectangleShape& playerHitbox, 
                    const std::vector<Enemy>& others);

    void chasePlayer(float deltaTime, const std::vector<std::vector<int>>& map,
                    const sf::RectangleShape& playerHitbox,
                    const std::vector<Enemy>& others);

  public:
    bool alive = true;

    Enemy(int id, sf::Vector2f startPos, int diff);
    int getNumber() const;

    void update(float deltaTime, const std::vector<std::vector<int>>& map, 
                const sf::RectangleShape& playerHitbox, 
                const std::vector<Enemy>& others);

    void draw(sf::RenderWindow& window) const;
    const sf::RectangleShape& getHitbox() const;
    virtual ~Enemy();

};
