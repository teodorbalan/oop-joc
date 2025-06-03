#include "Player.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Player::Player() {
  healthBarBack.setSize({200.f, 20.f});
  healthBarBack.setFillColor(sf::Color(100, 100, 100)); 
  healthBarBack.setPosition({20.f, 20.f}); 

  healthBarFront.setSize({200.f, 20.f});
  healthBarFront.setFillColor(sf::Color::Red);
  healthBarFront.setPosition({20.f, 20.f});

  hitbox.setSize({25.f, 45.f});
  hitbox.setOrigin(hitbox.getSize() / 2.f); 
  hitbox.setFillColor(sf::Color::Transparent);
  hitbox.setOutlineColor(sf::Color::Transparent);
  hitbox.setOutlineThickness(1.f);
  hitbox.setPosition({150.f, 150.f});

  loadTextures();
  sprite = sf::Sprite(textures[0]);
  sf::FloatRect bounds = sprite -> getLocalBounds();
  sprite -> setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
  sprite -> setPosition(hitbox.getPosition());
}

void Player::loadTextures() {
  textures.resize(11);
  for(int i = 0; i < 11; ++i) {
    std::stringstream ss;
    ss << "./assets/photos/student/tile" << std::setw(3) << std::setfill('0') << (i) << ".png";
    if (!textures[i].loadFromFile(ss.str())) {
      std::cerr << "Failed to load: " << ss.str() << "\n";
    }
  }
}

bool Player::canMoveTo(sf::Vector2f position, const std::vector<std::vector<int>>& map) {
  const float minDistance = 5.f;

  sf::Vector2f size = hitbox.getSize();
  sf::Vector2f half = size / 2.f;

  std::vector<sf::Vector2f> points = {
    position + sf::Vector2f(-half.x + minDistance, -half.y + minDistance), // top-left
    position + sf::Vector2f( half.x - minDistance, -half.y + minDistance), // top-right
    position + sf::Vector2f(-half.x + minDistance,  half.y - minDistance), // bottom-left
    position + sf::Vector2f( half.x - minDistance,  half.y - minDistance)  // bottom-right
  };

  for(const auto& point : points) {
    int xTile = static_cast<int>(point.x / tileSize);
    int yTile = static_cast<int>(point.y / tileSize);

    if (xTile < 0 || yTile < 0 || yTile >= map.size() || xTile >= map[0].size())
      return false;

    if (map[yTile][xTile] == 2) // wall
      return false;
  }

  return true;
}

void Player::handleInput(float deltaTime, const std::vector<std::vector<int>>& map) {
  sf::Vector2f movement(0.f, 0.f);
  bool moved = false;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    movement.y -= speed * deltaTime;
    direction = 3; // up
    moved = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    movement.y += speed * deltaTime;
    direction = 0; // down
    moved = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    movement.x -= speed * deltaTime;
    direction = 1; // left
    moved = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    movement.x += speed * deltaTime;
    direction = 2; // right
    moved = true;
  }

   if (movement.y != 0.f) {
    sf::Vector2f newPosY = hitbox.getPosition() + sf::Vector2f(0.f, movement.y);
    if (canMoveTo(newPosY, map)) {
      hitbox.move({0.f, movement.y});
      sprite->move({0.f, movement.y});
    }
  }
  if (movement.x != 0.f) {
    sf::Vector2f newPosX = hitbox.getPosition() + sf::Vector2f(movement.x, 0.f);
    if (canMoveTo(newPosX, map)) {
      hitbox.move({movement.x, 0.f});
      sprite->move({movement.x, 0.f});
    }
  }

  if (moved) {
    updateAnimation(deltaTime);
  } else {
    animationTimer = 0.f;        
    currentFrame = 1;            
    sprite -> setTexture(textures[direction * 3 + currentFrame]);
  }
}

void Player::updateAnimation(float deltaTime) {
  animationTimer += deltaTime;
  if (animationTimer >= 0.05f) {
    animationTimer = 0.f;
    currentFrame = (currentFrame + 1) % 3; 
    int texIndex = direction * 3 + currentFrame;
    if (texIndex < textures.size()) {
      sprite -> setTexture(textures[texIndex]);
    }
  }
}

void Player::update(float deltaTime) {
}

void Player::draw(sf::RenderWindow& window) const {
  window.draw(*sprite);
  window.draw(hitbox); 
}

sf::Vector2f Player::getPosition() const {
  return hitbox.getPosition();
}

void Player::setPosition(sf::Vector2f pos) {
  hitbox.setPosition(pos);
  sprite -> setPosition(pos);
}

const sf::RectangleShape& Player::getShape() const {
  return hitbox;
}

void Player::changeHealth(float amount) {
  currentHealth += amount;
  if (currentHealth < 0.f) currentHealth = 0.f;
  if (currentHealth > maxHealth) currentHealth = maxHealth;

  float percent = currentHealth / maxHealth;
  healthBarFront.setSize({200.f * percent, 20.f});
}

void Player::drawUI(sf::RenderWindow& window) const {
  window.setView(window.getDefaultView()); 
  window.draw(healthBarBack);
  window.draw(healthBarFront);
}

float Player::getHealth() const {
  return currentHealth;
}

