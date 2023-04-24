#include "player.h"

Player::Player(int x, int y, int w, int h, float playerAcceleration, std::size_t maxHealth) : BaseGameObject(x, y, w, h, playerAcceleration, maxHealth, 1)
{
}

Player::~Player()
{
    //todo: cleanup
}


