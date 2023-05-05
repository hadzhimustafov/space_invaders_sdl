#ifndef BASE_GAME_OBJECT_H
#define BASE_GAME_OBJECT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

enum CollisionDirection {
    Up, Down
};
enum MovementDirection {
    None, Left, Right
};

class BaseGameObject {
protected:
    /// owned resources
    SDL_Rect _position{};
    SDL_Texture *tex = nullptr;
    float _speed{0};
    float _speedAcceleration{0};
    int _killingScore{0};
    float _currentSpeed{0};
    std::size_t _health, _maxHealth;
    std::size_t _bulletDamage;
    MovementDirection _direction{None};

public:
    BaseGameObject(int x, int y, int w, int h);

    BaseGameObject(int x, int y, int w, int h, float speedAcceleration, std::size_t maxHealth, std::size_t bulletDamage);

    ~BaseGameObject();

    //presentation
    void SetImage(const std::string &filename, SDL_Renderer *ren);

    virtual void Draw(SDL_Renderer *ren) const;

    //movement
    void SetDirection(MovementDirection direction);

    float GetCurrentSpeed() const;

    void SetSpeed(float speed);

    void Accelerate();

    SDL_Rect GetPosition() const { return _position; }


    //collision
    bool HasCollision(const BaseGameObject *gameObject, CollisionDirection direction) const;

    bool GetIsDestroyed() const { return _health <= 0; }

    void TakeDamage();

    //scoring & health
    int GetKillingScore() const { return _killingScore; }

    void SetKillingScore(int score) { _killingScore = score; }

    std::size_t GetHealth() const { return _health; }

    std::size_t GetMaxHealth() const { return _maxHealth; }
};

#endif