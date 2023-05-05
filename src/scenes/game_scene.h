#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <vector>
#include "game_objects/bullet.h"
#include "game_objects/alien.h"
#include "game_objects/player.h"
#include "game_objects/obstacle.h"
#include "scene.h"

constexpr int AlienWidth{50};
constexpr int AlienHeight{30};
constexpr int AlienSpacing{10};
constexpr int AliensColumnsCount{7};
constexpr int AliensRowsCount{5};
constexpr int AlienSpeed{4};
constexpr float AlienSpeedAcceleration{0.25f};
constexpr int AliensKillingScore{500};

constexpr int PlayerWidth{50};
constexpr int PlayerHeight{50};
constexpr int PlayerSpeed{4};
constexpr int PlayerHealth{3};
constexpr float PlayerSpeedAcceleration{0.02f};

constexpr int BulletWidth{9};
constexpr int BulletHeight{20};
constexpr int BulletSpeed{5};

constexpr int ObstacleWidth{25};
constexpr int ObstacleHeight{25};
constexpr int ObstacleCount{5};
constexpr int ObstacleKillingScore{100};
constexpr int ObstacleSpacing{1};
constexpr int ObstacleMargin{50};
constexpr int ObstacleShapeMap[3][5]{
{0,1,1,1,0},
{1,1,1,1,1},
{1,0,0,0,1}
};

const std::string AlienImagePath = "res/alien.png";
const std::string PlayerImagePath = "res/player.png";
const std::string AlienBulletImagePath = "res/alien_laser.png";
const std::string PlayerBulletImagePath = "res/player_laser.png";
const std::string ObstacleImagePath = "res/metal_blocks.png";


class GameScene : public Scene
{
private:
    std::vector<std::unique_ptr<Bullet>> _bullets;
    std::vector<std::unique_ptr<Alien>> _aliens;
    std::vector<std::unique_ptr<Obstacle>> _obstacles;
    std::unique_ptr<Player> _player;
    std::size_t _bulletCounter{0};
    int _aliensWave{0};

    bool getIfAliensWillReachEdge();
    void moveAliens(SDL_Renderer *renderer);
    void moveBullets();
    void applyCollisions();
    bool getIfAliensReachedTarget();
    void placeObstacle(int &id, int x, SDL_Renderer *renderer);
    void placeObstacles(SDL_Renderer *renderer);
    void placeAlien(std::size_t id, int x, int y, SDL_Renderer *renderer);
    void placeAliens(SDL_Renderer *renderer);
    void placeBullet(int x, int y, bool isAlienBullet, SDL_Renderer *renderer);
    template <typename T> void removeDestroyedObjects(std::vector<std::unique_ptr<T>> &objects);
    template <typename T> bool checkIfBulletHitSomething(const Bullet *bullet, std::vector<std::unique_ptr<T>> &objects, CollisionDirection direction);

public:
    explicit GameScene(Game *game);
    void Load() override;
    void OnUpdate() override;
    void OnDraw() const override;
    void OnDrawHud() const override;
    void OnLeft() override;
    void OnRight() override;
    void OnResetHorizontal() override;
    void OnPlayerShoot() override;
    void OnExit() const override;
};




#endif
