#include <algorithm>
#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include "game_scene.h"
#include "cleanup.h"

bool GameScene::getIfAliensWillReachEdge() {
    auto renderSize = _game->GetSize();
    auto checkIfAlienWillReachEdgePredicate = [&renderSize](std::unique_ptr<Alien> &a) {
        return a->WillReachEdge(renderSize.x, renderSize.w);
    };
    return std::any_of(_aliens.begin(), _aliens.end(), checkIfAlienWillReachEdgePredicate);
}

// todo: split & rename: |move|shoot|die|
void GameScene::moveAliens(SDL_Renderer *renderer) {
    bool aliensReachEdge = getIfAliensWillReachEdge();

    for (std::unique_ptr<Alien> &alien: _aliens) {
        auto direction = alien->GetMovementDirection();
        if(aliensReachEdge) {
            direction = direction == Left ? Right : Left;
            alien->SetMovementDirection(direction);
        }
        auto position = alien->GetPosition();
        auto x = position.x + alien->GetUpdatedCurrentSpeed();
        auto y = aliensReachEdge ? position.y + position.h / 2 : position.y;
        alien->SetPosition(x, y);
        if (alien->GetIfTimeToShoot()) {
            auto bulletX = x + AlienWidth / 2 - BulletWidth / 2;
            auto bulletY = y + AlienHeight;
            _bulletCounter++;
            auto bullet = std::make_unique<Bullet>(_bulletCounter, bulletX, bulletY, BulletWidth, BulletHeight);
            bullet->SetImage(AlienBulletImagePath, renderer);
            bullet->SetIsAlien(true);
            bullet->SetSpeed(BulletSpeed);
            _bullets.emplace_back(std::move(bullet));
        }
    }
}

void GameScene::moveBullets() {
    for (std::unique_ptr<Bullet> &bullet: _bullets) {
        auto position = bullet->GetPosition();
        auto speed = bullet->GetSpeed();
        std::size_t y = position.y + speed;
        bullet->SetPosition(position.x, y);
    }
}

void GameScene::checkForCollisions() {
    bool hit = false;
    CollisionDirection direction;

    for (auto &&bullet: _bullets) {
        Bullet &bulletRef = *bullet;
        hit = false;
        direction = bulletRef.GetIsAlien() ? CollisionDirection::Down : CollisionDirection::Up;
        hit = checkIfBulletShotSomething(bulletRef, _obstacles, direction);
        if (!hit && direction == CollisionDirection::Up) {
            hit = checkIfBulletShotSomething(bulletRef, _aliens, direction);
        } else if (!hit) {
            hit = _player->HasCollision(bulletRef, direction);
            if (hit) {
                _player->TakeDamage();
            }
        }

        auto bulletPosition = bulletRef.GetPosition();
        bool bulletReachedEdge = bulletPosition.y <= 0 || bulletPosition.y + bulletPosition.h >= SCREEN_HEIGHT;
        if (bulletReachedEdge || hit) {
            bulletRef.TakeDamage();
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
        auto des = target.GetIsDestroyed();
        if (des) {
            const std::type_info &objType = typeid(target);
            printf("<<<%s DESTROYED>>%d\n", objType.name(), static_cast<int>(target.GetId()));
        }
        return des;
    });
    objects.erase(newEnd, objects.end());
    fflush(stdout);
}

template<typename T>
bool GameScene::checkIfBulletShotSomething(const Bullet &bullet,
                                           std::vector<std::unique_ptr<T>> &objects,
                                           CollisionDirection direction) {
    auto checkForCollision = [bullet, direction]
            (const std::unique_ptr<T> &obj) { return (*obj).HasCollision(bullet, direction); };
    auto shotTarget = std::find_if(objects.begin(), objects.end(), checkForCollision);

    if (shotTarget == objects.end()) return false;

    auto &&target = *shotTarget;
    target->TakeDamage();

    if(!bullet.GetIsAlien()){
        auto killScore = target->GetKillingScore();
        _game->SetScore(_game->GetScore() + killScore);
    }
    return true;
}

GameScene::GameScene(Game *game) : _game(game) {
}

GameScene::~GameScene() {
}

void GameScene::Load() {
    auto renderer = _game->GetRenderer();
    placeAliens(renderer);
    placeObstacles(renderer);

    auto renderSize = _game->GetSize();
    int x = (renderSize.w - PlayerWidth) / 2;
    int y = renderSize.h - PlayerHeight - 10;
    _player = std::make_unique<Player>(x, y, PlayerWidth, PlayerHeight, PlayerSpeedAcceleration, PlayerHealth);
    _player->SetImage(PlayerImagePath, renderer);
    _player->SetSpeed(PlayerSpeed);
}

void GameScene::OnUpdate() {
    auto renderer = _game->GetRenderer();
    movePlayer();
    moveAliens(renderer);
    moveBullets();
    checkForCollisions();

    if (_aliens.empty()) {
        placeAliens(renderer);
    } else if (_player->GetIsDestroyed()) {
        _game->GameOver();
    } else  if(getIfAliensReachedTarget()){
        _game->GameOver();
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

void GameScene::OnDrawHud(SDL_Color &color, TTF_Font *font) const {
    auto renderer = _game->GetRenderer();
    std::string scoreMessage{"Score:" + std::to_string(_game->GetScore())};
    displayText(scoreMessage, 20, 20, renderer, color, font);

    std::string healthMessage{"Health: " + std::to_string(_player->GetHealth()) + "/" + std::to_string(_player->GetMaxHealth())};
    displayText(healthMessage, SCREEN_WIDTH - 250,  20, renderer, color, font);
}

void GameScene::OnLeft() {
    _player->SetMovementDirection(Left);
}

void GameScene::OnRight() {
    _player->SetMovementDirection(Right);
}

void GameScene::OnResetHorizontal() {
    _player->SetMovementDirection(None);
}

void GameScene::OnPlayerShoot() {
    auto renderer = _game->GetRenderer();
    auto playerPosition = _player->GetPosition();
    std::size_t bulletX = playerPosition.x + PlayerWidth / 2 - BulletWidth / 2;
    std::size_t bulletY = playerPosition.y - PlayerHeight + BulletHeight;
    _bulletCounter++;
      auto bullet = std::make_unique<Bullet>(_bulletCounter, bulletX, bulletY, BulletWidth, BulletHeight);
    bullet->SetImage(PlayerBulletImagePath, renderer);
    bullet->SetSpeed(-BulletSpeed);
    _bullets.emplace_back(std::move(bullet));
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
    int rows = sizeof(ObstacleShapeMap)/sizeof(ObstacleShapeMap[0]);
    int cols = sizeof(ObstacleShapeMap[0])/sizeof(ObstacleShapeMap[0][0]);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if(!ObstacleShapeMap[row][col]) continue;
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

    for (size_t column = 0; column < AliensColumnsCount; column++) {
        for (size_t row = 0; row < AliensRowsCount; row++) {
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
    alien->SetMovementDirection(Left);
    _aliens.emplace_back(std::move(alien));
}

void GameScene::displayText(const std::string& message, int x, int y, SDL_Renderer *renderer, SDL_Color &color, TTF_Font *font) {
    SDL_Rect rect;
    auto surf = TTF_RenderText_Solid(font, message.c_str(), color);
    auto tex = SDL_CreateTextureFromSurface(renderer, surf);
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;
    SDL_RenderCopy(renderer, tex, nullptr, &rect);
    cleanup(surf, tex);
}

void GameScene::movePlayer() {
    auto playerSpeed = _player->GetUpdatedCurrentSpeed();
    auto renderSize = _game->GetSize();
    auto playerPosition = _player->GetPosition();
    auto newX = playerPosition.x + playerSpeed;
    if (newX <= 0 || newX + PlayerWidth >= renderSize.x + renderSize.w) {
        return;
    }
    _player->SetPosition(newX, playerPosition.y);
}

bool GameScene::getIfAliensReachedTarget() {
    for (auto &&alien:_aliens) {
        if(alien->HasCollision(*_player, CollisionDirection::Up)){
            return true;
        }

        auto position = alien->GetPosition();
        if(position.y + position.h >= SCREEN_HEIGHT){
            return true;
        }
    }
    return false;
}


