#include "alien.h"

bool Alien::GetIfTimeToShoot()
{
    _shootTimer--;
    if (_shootTimer <= 0)
    {
        _shootTimer = random(engine);
        return true;
    }
    return false;
}

bool Alien::WillReachEdge(int leftEdge, int rightEdge)
{
    auto x = _position.x + static_cast<int>(GetCurrentSpeed());
    if (x <= leftEdge || x + _position.w >= rightEdge)
    {
        return true;
    }

    return false;
}

void Alien::Move() {
    _position.x = _position.x + static_cast<int>(GetCurrentSpeed());
}

void Alien::ToggleDirection() {
    auto direction = _direction == Left ? Right : Left;
    SetDirection(direction);
    _position.y += _position.h;
}
