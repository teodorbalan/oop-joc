#include "Enemy.hpp"
#include <cstdlib>
#include <cmath>
#include <sstream>
#include "ResourceManager.hpp"
#include <iostream>


Enemy::Enemy(int id, sf::Vector2f startPos, int diff) {
  hitbox.setSize({30.f, 30.f});
  hitbox.setOrigin(hitbox.getSize() / 2.f);
  hitbox.setFillColor(sf::Color::Transparent);
  hitbox.setPosition(startPos);

  difficulty = diff;
  number = id;

  numberText = sf::Text(ResourceManager::getFont());
  numberText->setCharacterSize(34);
  numberText -> setFillColor(sf::Color::Red);
  numberText -> setString(std::to_string(number));
  sf::FloatRect bounds = numberText -> getLocalBounds();
  numberText -> setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
  numberText -> setPosition(hitbox.getPosition());
}

Enemy::~Enemy() {
}


sf::Vector2f Enemy::getDirectionVector() const {
  switch (direction) {
    case 0: return {0.f, 1.f};
    case 1: return {-1.f, 0.f};
    case 2: return {1.f, 0.f};
    case 3: return {0.f, -1.f};
    default: return {0.f, 0.f};
  }
}

bool Enemy::canMoveTo(sf::Vector2f pos, const std::vector<std::vector<int>>& map, 
                      const sf::RectangleShape& playerHitbox, 
                      const std::vector<Enemy>& others) const {
  int xTile = static_cast<int>(pos.x / tileSize);
  int yTile = static_cast<int>(pos.y / tileSize);

  if (xTile < 0 || yTile < 0 || yTile >= static_cast<int>(map.size()) || xTile >= static_cast<int>(map[0].size()))
    return false;

  if (map[yTile][xTile] != 1)
    return false;

  sf::Vector2f size = hitbox.getSize();
  sf::FloatRect futureBounds(
    pos - size / 2.f,  
    size               
  );

  if (futureBounds.findIntersection(playerHitbox.getGlobalBounds())) {
    const_cast<Enemy*>(this)->alive = false;
    return false;
  }

  for (const auto& other : others) {
    if (&other == this) continue;
    if (futureBounds.findIntersection(other.hitbox.getGlobalBounds()))
      return false;
  }

  return true;
}

void Enemy::moveRandom(float deltaTime, const std::vector<std::vector<int>>& map, 
                       const sf::RectangleShape& playerHitbox, 
                       const std::vector<Enemy>& others) {
  decisionTimer -= deltaTime;
  if (decisionTimer <= 0.f) {
    direction = std::rand() % 4;
    decisionTimer = 1.f + static_cast<float>(std::rand() % 100) / 50.f; // 1–3 sec
  }

  sf::Vector2f dir = getDirectionVector();
  sf::Vector2f movement = dir * speed * deltaTime;
  sf::Vector2f newPos = hitbox.getPosition() + movement;

  if (canMoveTo(newPos, map, playerHitbox, others)) {
    hitbox.move(movement);
  }
}

void Enemy::chasePlayer(float deltaTime, const std::vector<std::vector<int>>& map,
                        const sf::RectangleShape& playerHitbox,
                        const std::vector<Enemy>& others) {
  sf::Vector2f toPlayer = playerHitbox.getPosition() - hitbox.getPosition();
  float dx = std::abs(toPlayer.x), dy = std::abs(toPlayer.y);
  sf::Vector2f moveDir;

  if (dx > dy) {
    moveDir.x = (toPlayer.x > 0) ? 1.f : -1.f;
  } else {
    moveDir.y = (toPlayer.y > 0) ? 1.f : -1.f;
  }

  sf::Vector2f movement = moveDir * speed * deltaTime;
  sf::Vector2f newPos = hitbox.getPosition() + movement;

  if (canMoveTo(newPos, map, playerHitbox, others)) {
    hitbox.move(movement);
  }
}

void Enemy::update(float deltaTime, const std::vector<std::vector<int>>& map, 
                   const sf::RectangleShape& playerHitbox, 
                   const std::vector<Enemy>& others) {
  // std::cout << "Enemy " << number << " updating, alive: " << alive << "\n";


  if (!alive) return;
  if (number <= 4)
    chasePlayer(deltaTime, map, playerHitbox, others);
  else
    moveRandom(deltaTime, map, playerHitbox, others);

  numberText -> setPosition(hitbox.getPosition());
}

void Enemy::draw(sf::RenderWindow& window) const {
  window.draw(hitbox);
  window.draw(*numberText);
}

const sf::RectangleShape& Enemy::getHitbox() const {
  return hitbox;
}

int Enemy::getNumber() const {
  return number;
}
