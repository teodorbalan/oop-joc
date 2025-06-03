#include "GameScene.hpp"
#include <iostream>
#include "Enemy.hpp"
#include <vector>
#include <queue>
#include <random>   
#include <ctime>    
#include "ResourceManager.hpp"


// 1 - floor, 2 - wall, 3 - door

std::vector<std::string> charMap = {
  "2222222222200000000000000000000000000000000000000000000000000000000000000000",
  "2111111111222222220000000000000000000000000000000000000000000000000000000000",
  "2111111111311111120000000000000000000000000000000000000000000000000000000000",
  "2111111111222222120000000000000000000000000000000000000000000000000000000000",
  "2222222222200002120000000000000000000000000000000000000000000000000000000000",
  "0000000000000002120000000000000000000000000000000000000000000000000000000000",
  "0000022222222222322222222200000000000000000000000000000000000000000000000000",
  "0000021111111111111111111200000000000000000000000000000000000000000000000000",
  "0000021111111111111111111200000000000000000000000000000000000000000000000000",
  "0000021111111111111111111200000000000000000000000000000000000000000000000000",
  "0000021111111111111111111200000000000000000000000000000000000000000000000000",
  "0000022222222222122222222200000000000000000000000000000000000000000000000000",
  "000000000000002232222222200000000000000000000000000000000000000000000000000",
  "0000000000000021111111111200000000000000000000000000000000000000000000000000",
  "0000000000000021111111111200000000000000000000000000000000000000000000000000",
  "0000000000000021111111111200000000000000000000000000000000000000000000000000",
  "0000000000000021111111111200000000000000000000000000000000000000000000000000",
  "0000000000000021111111111200000000000000000000000000000000000000000000000000",
  "0000000000000021111111111200000000000000000000000000000000000000000000000000",
  "0000000000000022222222322200000000000000000000000000000000000000000000000000",
  "0000000000000000000021112000000000000000000000000000000000000000000000000000",
  "0000000000000000000021112000000000000000000000000000000000000000000000000000",
  "0000000000000000000021112000000000000000000000000000000000000000000000000000",
  "0000000000000000000021112000000000000000000000000000000000000000000000000000",
  "0000000000000000000021112000000000000000000000000000000000000000000000000000",
  "0000000000000000000021112000000000000000000000000000000000000000000000000000",
  "0000000000000000000021112000000000000000000000000000000000000000000000000000",
  "0000000000000000000021112000000000000000000000000000000000000000000000000000",
  "0000000222222222222222322222222222222222222222222222000000000000000000000000",
  "0000000211221111111111111111111111221111211111111112000000000000000000000000",
  "0000000211221112111111111111112111221111211111112112000000000000000000000000",
  "0000000211221111111122111111111111221111311121111112000000000000000000000000",
  "0000000211111121111122211111121111221111211121111212000000000000000000000000",
  "0000000211111111111111111111111111111111222222322222000000000000000000000000",
  "0000000211111111111111111111111111111111211111111120000000000000000000000000",
  "0000000211111111111111111111111111111111211121111220000000000000000000000000",
  "0000000211111111111111111111111111111111311121121120000000000000000000000000",
  "0000000211111111111111111111111111111111211111121120000000000000000000000000",
  "0000000211111111111111111111111111111111211121111120000000000000000000000000",
  "0000000222222222222222222222222222222222222222222220000000000000000000000000",
};

GameScene::GameScene() {
  if(!backgroundMusic.openFromFile("./assets/audio/menuAudio.mp3")) {
  } else {
    backgroundMusic.setLooping(false); 
    backgroundMusic.setPlayingOffset(sf::seconds(5.f));
    backgroundMusic.setVolume(20.f); 
    backgroundMusic.play();
  }
  badGradeMusic.openFromFile("./assets/audio/badGradeMusic.mp3");
  goodGradeMusic.openFromFile("./assets/audio/goodGradeMusic.mp3");
  nextLevelMusic.openFromFile("./assets/audio/nextLevelMusic.mp3");
  failedSessionMusic.openFromFile("./assets/audio/failedSessionMusic.mp3");

  deadTexture.loadFromFile("./assets/photos/dead.png");
  deadSprite.emplace(deadTexture);
  deadSprite->setOrigin({deadTexture.getSize().x / 2.f, deadTexture.getSize().y / 2.f});
  deadSprite->setPosition({1280.f / 2.f, 720.f / 2.f});
  deadSprite->setScale({2.f, 2.f});

  deadText = sf::Text(ResourceManager::getFont());
  deadText->setCharacterSize(44);
  deadText->setFillColor(sf::Color(240, 20, 20));
  deadText->setString("Ai picat examenul fraiere!");
  deadText->setPosition({1280.f / 2.f - 200.f, 720.f / 2.f - 100.f});



  view.setSize({1280.f, 720.f}); 
  view.setCenter(player.getPosition());


  floorTexture.loadFromFile("./assets/photos/floor.png");
  floor.setSize({tileSize, tileSize}); 
  floor.setTexture(&floorTexture);

  wallTexture.loadFromFile("./assets/photos/wall.png");
  wall.setSize({tileSize, tileSize}); 
  wall.setTexture(&wallTexture);

  doorTexture.loadFromFile("./assets/photos/door.png");
  door.setSize({tileSize, tileSize});
  door.setTexture(&doorTexture);

  map.resize(mapHeight, std::vector<int>(mapWidth, 0)); // 0 = tile, 1 = wall, 2 = door

   for(int y = 0; y < charMap.size(); y++) {
    for(int x = 0; x < charMap[0].size(); x++) {
      char tile = charMap[y][x];
      if (tile == '1') {
        map[y][x] = 1; // floor
      } else if (tile == '2') {
        map[y][x] = 2; // wall
      } else if (tile == '3') {
        map[y][x] = 3; // door
      } 
    }
  }
  // generateEnemyLevel();

}

std::optional<std::string> GameScene::handleEvents(sf::RenderWindow& window) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>())
      window.close();
    else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && player.getHealth() <= 0.f) {
        return "menu"; 
    } else if(event->is<sf::Event::MouseButtonPressed>() && player.getHealth() <= 0.f) 
        return "menu";
    }
  }
  return std::nullopt;
}

void GameScene::update(float deltaTime) {
  if(player.getHealth() <= 0.f) {
    return; 
  }


  player.handleInput(deltaTime, map);
  player.update(deltaTime);
  view.setCenter(player.getPosition());
  for(auto& enemy : enemies) {
    enemy.update(deltaTime, map, player.getShape(), enemies);
    if(!enemy.alive) {
      int number = enemy.getNumber();
      std::cout << number;
      if (number <= 4) {
        player.changeHealth(10.f * number - 50.f); // damage
        badGradeMusic.setVolume(80.f); 
        badGradeMusic.play();
      }
      else {
        player.changeHealth(5.f * 10);  // heal
        goodGradeMusic.setVolume(50.f);
        goodGradeMusic.play();
      }
    }
  }

    
  enemies.erase(
    std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) {
      return !e.alive;
    }),
    enemies.end()
  );

  if (doorCooldown > 0.f)
    doorCooldown -= deltaTime;

  sf::Vector2f pos = player.getPosition();
  int px = static_cast<int>(pos.x / tileSize);
  int py = static_cast<int>(pos.y / tileSize);

  if (px >= 0 && py >= 0 && py < mapHeight && px < mapWidth) {
    if (map[py][px] == 3 && doorCooldown <= 0.f) {
      level++;
      if(level >= 2) {
        nextLevelMusic.setVolume(50.f);
        nextLevelMusic.play();
      } 
      if(level >= 2) {
        map[py][px] = 2;
        player.setPosition({pos.x + tileSize * 1, pos.y + tileSize * 1.5}); 
        generateEnemyLevel();
      }
      doorCooldown = 2.f; 
    }
  }

  if (backgroundMusic.getStatus() == sf::SoundSource::Status::Stopped) {
    backgroundMusic.setPlayingOffset(sf::seconds(5.f)); 
    backgroundMusic.play();
  }

  if(player.getHealth() <= 0.f) {
    backgroundMusic.stop();
    badGradeMusic.stop();
    goodGradeMusic.stop();
    nextLevelMusic.stop();
    failedSessionMusic.setVolume(50.f);
    failedSessionMusic.play();
  }
}

void GameScene::render(sf::RenderWindow& window) {
  view.setCenter(player.getPosition());  
  window.setView(view);
  window.clear(sf::Color(52, 63, 128));

  // Render map
  for(int y = 0; y < mapHeight; y++) {
    for(int x = 0; x < mapWidth; x++) {
      if(map[y][x] == 1) { // floor
        floor.setPosition({x * tileSize, y * tileSize});
        window.draw(floor);
      } else if(map[y][x] == 2) { // wall
        wall.setPosition({x * tileSize, y * tileSize});
        window.draw(wall);
      } else if(map[y][x] == 3) { // door
        door.setPosition({x * tileSize, y * tileSize});
        window.draw(door);
      }
    }
  }
  for(const auto& enemy : enemies)
    enemy.draw(window);

  player.draw(window);
  player.drawUI(window);

  if(player.getHealth() <= 0.f) {
    window.draw(*deadSprite); 
    window.draw(*deadText); 
  }

  window.display();
}

std::vector<sf::Vector2i> GameScene::getNeighbors(sf::Vector2i pos) {
  return {
    {pos.x + 1, pos.y}, {pos.x - 1, pos.y},
    {pos.x, pos.y + 1}, {pos.x, pos.y - 1}
  };
}

std::vector<sf::Vector2i> GameScene::floodFillRoom(sf::Vector2i start) {
  std::vector<sf::Vector2i> room;
  std::vector<std::vector<bool>> visited(mapHeight, std::vector<bool>(mapWidth, false));
  std::queue<sf::Vector2i> q;

  q.push(start);
  visited[start.y][start.x] = true;

  while (!q.empty()) {
    sf::Vector2i current = q.front(); q.pop();
    if (map[current.y][current.x] != 1) continue;

    room.push_back(current);

    for (const auto& neighbor : getNeighbors(current)) {
      if (neighbor.x < 0 || neighbor.y < 0 || neighbor.x >= mapWidth || neighbor.y >= mapHeight)
        continue;

      if (!visited[neighbor.y][neighbor.x] && map[neighbor.y][neighbor.x] == 1) {
        visited[neighbor.y][neighbor.x] = true;
        q.push(neighbor);
      }
    }
  }

  return room;
}

void GameScene::generateEnemyLevel() {
  enemies.clear();

  sf::Vector2f playerPos = player.getPosition();
  int playerX = static_cast<int>(playerPos.x / tileSize);
  int playerY = static_cast<int>(playerPos.y / tileSize);

  std::vector<sf::Vector2i> room = floodFillRoom({playerX, playerY});

  std::vector<sf::Vector2i> spawnTiles;
  for (const auto& tile : room) {
    int dx = tile.x - playerX;
    int dy = tile.y - playerY;
    if (std::abs(dx) >= 2 || std::abs(dy) >= 2)
      spawnTiles.push_back(tile);
  }
  std::shuffle(spawnTiles.begin(), spawnTiles.end(), std::mt19937(std::random_device{}()));

  int totalEnemies = std::min((int)spawnTiles.size(), 3 + level + rand() % 3);
  int enemyCount = totalEnemies * 0.6; // 60% bad
  int goodEnemyCount = totalEnemies - enemyCount;

  int tileIndex = 0;

  for (int i = 0; i < enemyCount && tileIndex < spawnTiles.size(); ++i, ++tileIndex) {
    int type = (rand() % 4) + 1;
    sf::Vector2f spawnPos(spawnTiles[tileIndex].x * tileSize + tileSize / 2.f,
                          spawnTiles[tileIndex].y * tileSize + tileSize / 2.f);
    enemies.emplace_back(type, spawnPos, level);
  }

  for (int i = 0; i < goodEnemyCount && tileIndex < spawnTiles.size(); ++i, ++tileIndex) {
    int type = (rand() % 5) + 5;
    sf::Vector2f spawnPos(spawnTiles[tileIndex].x * tileSize + tileSize / 2.f,
                          spawnTiles[tileIndex].y * tileSize + tileSize / 2.f);
    enemies.emplace_back(type, spawnPos, level);
  }
}



