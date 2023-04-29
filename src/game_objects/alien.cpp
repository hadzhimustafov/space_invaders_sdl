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
    auto x = _position.x + _speed;
    if (x <= leftEdge || x + _position.w >= rightEdge)
    {
        return true;
    }

    return false;
}
