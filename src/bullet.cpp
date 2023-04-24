#include "bullet.h"

Bullet::Bullet(std::size_t id, int x, int y, int w, int h) : BaseGameObject(x, y, w, h,0, 1, 1), _id(id)
{
}

Bullet::~Bullet()
{
}