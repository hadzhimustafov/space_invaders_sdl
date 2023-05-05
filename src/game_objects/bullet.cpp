#include "bullet.h"

Bullet::Bullet(std::size_t id, int x, int y, int w, int h)
: BaseGameObject(x, y, w, h,1, 1, 1), _id(id)
{
}

void Bullet::Move() {
    _position.y = _position.y + static_cast<int>(_speed);
}
