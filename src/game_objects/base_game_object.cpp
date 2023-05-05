#include <iostream>
#include "base_game_object.h"
#include "logger.h"
#include "cleanup.h"

BaseGameObject::BaseGameObject(int x, int y, int w, int h)
: BaseGameObject(x, y, w, h, 0, 1, 1)
{
}

BaseGameObject::BaseGameObject(int x, int y, int w, int h, float speedAcceleration, std::size_t maxHealth, std::size_t bulletDamage)
: _speedAcceleration(speedAcceleration), _health(maxHealth), _maxHealth(maxHealth), _bulletDamage(bulletDamage)
{
    _position.x = x;
    _position.y = y;
    _position.w = w;
    _position.h = h;
}

BaseGameObject::~BaseGameObject() {
    cleanup(tex);
}

void BaseGameObject::SetImage(const std::string &filename, SDL_Renderer *ren) {
    SDL_Surface *surf = IMG_Load(filename.c_str());
    if (surf == nullptr) {
        logSDLError(std::cout, "loading image failed: " + filename);
    }

    tex = SDL_CreateTextureFromSurface(ren, surf);
    if (tex == nullptr) {
        logSDLError(std::cout, "CreateTextureFromSurface failed" + filename);
    }
    cleanup(surf);
}

void BaseGameObject::Draw(SDL_Renderer *ren) const {
    if (SDL_RenderCopyEx(ren, tex, nullptr, &_position, 0, nullptr, SDL_FLIP_NONE) != 0) {
        logSDLError(std::cout, "Draw GameObject failure");
    }
}

bool BaseGameObject::HasCollision(const BaseGameObject *gameObject, CollisionDirection direction) const {
    auto bullet = gameObject->GetPosition();

    int bulletRight = bullet.x + bullet.w;
    int bulletLeft = bullet.x;
    int bulletHead = direction == CollisionDirection::Down ? bullet.y + bullet.h : bullet.y;

    int currentRight = _position.x + _position.w;
    int currentLeft = _position.x;
    int currentHead = direction == CollisionDirection::Down ? _position.y : _position.y + _position.h;

    bool verticalCollisionHappened =
            direction == CollisionDirection::Down ? (currentHead < bulletHead) : (currentHead > bulletHead);

    return (currentLeft < bulletRight &&
            currentRight > bulletLeft &&
            verticalCollisionHappened);
}

void BaseGameObject::Accelerate() {
    auto speedup = _currentSpeed * _speedAcceleration;
    _currentSpeed += speedup;
}

float BaseGameObject::GetCurrentSpeed() const {
    switch (_direction) {
        case MovementDirection::Left:
            return -_currentSpeed;
        case MovementDirection::Right:
            return _currentSpeed;
        default:
            return 0;
    }
}

void BaseGameObject::TakeDamage() {
    if (_health > _bulletDamage) {
        _health -= _bulletDamage;
    } else {
        _health = 0;
    }
}

void BaseGameObject::SetSpeed(float speed) {
    _speed = speed;
    _currentSpeed = speed;
}

void BaseGameObject::SetDirection(MovementDirection direction) {
    if (_direction == direction) return;
    _direction = direction;
    _currentSpeed = _speed;
}
