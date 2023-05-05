#include <algorithm>
#include <cstdio>
#include <typeinfo>
#include <iostream>
#include "game_scene.h"
#include "../hud_manager.h"

bool GameScene::getIfAliensWillReachEdge() {
    auto renderSize = Game::GetSize();
    auto checkIfAlienWillReachEdgePredicate = [&renderSize](std::unique_ptr<Alien> &a) {
        return a->WillReachEdge(renderSize.x, renderSize.w);
    };
    return std::any_of(_aliens.begin(), _aliens.end(), checkIfAlienWillReachEdgePredicate);
}

void GameScene::moveAliens(SDL_Renderer *renderer) {
    bool changeDirection = getIfAliensWillReachEdge();

    for (auto &&alien: _aliens) {
        if (changeDirection) {
            alien->ToggleDirection();
        } else {
            alien->Move();
        }

        if (alien->GetIfTimeToShoot()) {
            auto alienPosition = alien->GetPosition();
            auto bulletX = alienPosition.x + alienPosition.w / 2 - BulletWidth / 2;
            auto bulletY = alienPosition.y + alienPosition.h;
            placeBullet(bulletX, bulletY, true, renderer);
        }
    }
}

void GameScene::moveBullets() {
    for (auto &&bullet: _bullets) {
        bullet->Move();
    }
}

void GameScene::applyCollisions() {
    bool hit = false;
    CollisionDirection direction;

    for (auto &&bullet: _bullets) {
        hit = false;
        direction = bullet->GetIsAlien() ? CollisionDirection::Down : CollisionDirection::Up;
        hit = checkIfBulletHitSomething(bullet.get(), _obstacles, direction);
        if (!hit && direction == CollisionDirection::Up) {
            hit = checkIfBulletHitSomething(bullet.get(), _aliens, direction);
        } else if (!hit) {
            hit = _player->HasCollision(bullet.get(), direction);
            if (hit) {
                _player->TakeDamage();
            }
        }

        auto bulletPosition = bullet->GetPosition();
        bool bulletReachedEdge = bulletPosition.y <= 0 || bulletPosition.y + bulletPosition.h >= SCREEN_HEIGHT;
        if (bulletReachedEdge || hit) {
            bullet->TakeDamage();
        }
    }

    removeDestroyedObjects(_aliens);
    removeDestroyedObjects(_bullets);
    removeDestroyedObjects(_obstacles);
}

template<typename T>
void GameScene::removeDestroyedObjects(std::vector<std::unique_ptr<T>> &objects) {
    auto newEnd = std::remove_if(objects.begin(), objects.end(), [](const std::unique_ptr<T> &obj) {
        auto &&target = *obj;
        return target.GetIsDestroyed();
    });
    objects.erase(newEnd, objects.end());
    fflush(stdout);
}

template<typename T>
bool GameScene::checkIfBulletHitSomething(const Bullet *bullet,
                                          std::vector<std::unique_ptr<T>> &objects,
                                          CollisionDirection direction) {
    auto checkForCollision = [bullet, direction]
            (const std::unique_ptr<T> &obj) { return (*obj).HasCollision(bullet, direction); };
    auto hitTarget = std::find_if(objects.begin(), objects.end(), checkForCollision);

    if (hitTarget == objects.end()) return false;

    auto &&target = *hitTarget;
    target->TakeDamage();

    if (!bullet->GetIsAlien()) {
        auto killScore = target->GetKillingScore();
        _game->SetScore(_game->GetScore() + killScore);
    }
    return true;
}

GameScene::GameScene(Game *game) : Scene(game) {
}

void GameScene::Load() {
    auto renderer = _game->GetRenderer();
    placeAliens(renderer);
    placeObstacles(renderer);

    auto renderSize = Game::GetSize();
    int x = (renderSize.w - PlayerWidth) / 2;
    int y = renderSize.h - PlayerHeight - 10;
    _player = std::make_unique<Player>(x, y, PlayerWidth, PlayerHeight, PlayerSpeedAcceleration, PlayerHealth);
    _player->SetImage(PlayerImagePath, renderer);
    _player->SetSpeed(PlayerSpeed);
}

void GameScene::OnUpdate() {
    auto renderer = _game->GetRenderer();
    _player->Move();
    moveAliens(renderer);
    moveBullets();
    applyCollisions();


    if (_player->GetIsDestroyed()) {
        _game->GameOver();
        return;
    }
    if (getIfAliensReachedTarget()) {
        _game->GameOver();
        return;
    }
    if (_aliens.empty()) {
        placeAliens(renderer);
    }
}

void GameScene::OnDraw() const {
    auto renderer = _game->GetRenderer();
    for (auto &&alien: _aliens) {
        alien->Draw(renderer);
    }
    for (auto &&bullet: _bullets) {
        bullet->Draw(renderer);
    }
    for (auto &&obstacle: _obstacles) {
        obstacle->Draw(renderer);
    }
    _player->Draw(renderer);
}

void GameScene::OnDrawHud() const {
    auto hudManager = _game->GetHudManager();
    auto ren = _game->GetRenderer();
    std::string scoreMessage{"Score:" + std::to_string(_game->GetScore())};
    hudManager->DrawText(ren, scoreMessage.c_str(), 20, 5);

    std::string healthMessage{
            "Lives: " + std::to_string(_player->GetHealth()) + "/" + std::to_string(_player->GetMaxHealth())};
    hudManager->DrawText(ren, healthMessage.c_str(), 0, SCREEN_HEIGHT - PlayerHeight);

    std::string escMessage{
            "Press <ESC> to cancel"};
    hudManager->DrawText(ren, escMessage.c_str(), SCREEN_WIDTH - 500, 5);
}

void GameScene::OnLeft() {
    _player->SetDirection(Left);
}

void GameScene::OnRight() {
    _player->SetDirection(Right);
}

void GameScene::OnResetHorizontal() {
    _player->SetDirection(None);
}
void GameScene::OnExit() const {
    _game->GameOver();
}
void GameScene::OnPlayerShoot() {
    auto renderer = _game->GetRenderer();
    auto playerPosition = _player->GetPosition();
    auto bulletX = playerPosition.x + PlayerWidth / 2 - BulletWidth / 2;
    auto bulletY = playerPosition.y - PlayerHeight + BulletHeight;
    placeBullet(bulletX, bulletY, false, renderer);
}

void GameScene::placeObstacles(SDL_Renderer *renderer) {
    auto obstacleId = 1;
    auto blockSize = SCREEN_WIDTH / ObstacleCount + 1;
    for (auto i = 0; i < ObstacleCount; i++) {
        auto x = (i * blockSize) + (i * ObstacleSpacing) + ObstacleSpacing;
        placeObstacle(obstacleId, x, renderer);
    }
}

void GameScene::placeObstacle(int &id, int x, SDL_Renderer *renderer) {
    int rows = sizeof(ObstacleShapeMap) / sizeof(ObstacleShapeMap[0]);
    int cols = sizeof(ObstacleShapeMap[0]) / sizeof(ObstacleShapeMap[0][0]);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (!ObstacleShapeMap[row][col]) continue;
            auto newX = ObstacleMargin + x + (col * ObstacleWidth) + (col * ObstacleSpacing) + ObstacleSpacing;
            auto newY = OBSTACLE_POSITION + (row * ObstacleHeight) + (row * ObstacleSpacing) + ObstacleSpacing;
            auto obstacle = std::make_unique<Obstacle>(++id, newX, newY, ObstacleWidth, ObstacleHeight);
            obstacle->SetKillingScore(ObstacleKillingScore);
            obstacle->SetImage(ObstacleImagePath, renderer);
            _obstacles.emplace_back(std::move(obstacle));
        }
    }
}

void GameScene::placeAliens(SDL_Renderer *renderer) {
    _aliensWave++;

    for (auto column = 0; column < AliensColumnsCount; column++) {
        for (auto row = 0; row < AliensRowsCount; row++) {
            auto x = (column * AlienWidth) + (column * AlienSpacing) + AlienSpacing;
            auto y = (row * AlienHeight) + (row * AlienSpacing) + AlienSpacing;
            placeAlien(row + column, x, y, renderer);
        }
    }
}

void GameScene::placeAlien(std::size_t id, int x, int y, SDL_Renderer *renderer) {
    auto alien = std::make_unique<Alien>(id, x, y, AlienWidth, AlienHeight);
    auto alienSpeedUp = AlienSpeed * (AlienSpeedAcceleration * _aliensWave);
    alien->SetSpeed(AlienSpeed + alienSpeedUp);
    alien->SetKillingScore(AliensKillingScore);
    alien->SetImage(AlienImagePath, renderer);
    alien->SetDirection(Right);
    _aliens.emplace_back(std::move(alien));
}

bool GameScene::getIfAliensReachedTarget() {
    for (auto &&alien: _aliens) {
        if (alien->HasCollision(_player.get(), CollisionDirection::Up)) {
            return true;
        }

        auto position = alien->GetPosition();
        if (position.y + position.h >= SCREEN_HEIGHT) {
            return true;
        }
    }
    return false;
}

void GameScene::placeBullet(int x, int y, bool isAlienBullet, SDL_Renderer *renderer) {
    _bulletCounter++;
    auto bullet = std::make_unique<Bullet>(_bulletCounter, x, y, BulletWidth, BulletHeight);
    float bulletSpeed = isAlienBullet ? BulletSpeed : -BulletSpeed;
    auto bulletImage = isAlienBullet ? AlienBulletImagePath : PlayerBulletImagePath;
    bullet->SetImage(bulletImage, renderer);
    bullet->SetIsAlien(isAlienBullet);

    bullet->SetSpeed(bulletSpeed);
    _bullets.emplace_back(std::move(bullet));
}


