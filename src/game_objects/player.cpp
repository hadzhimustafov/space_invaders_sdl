#include "player.h"
#include "game.h"

Player::Player(int x, int y, int w, int h, float playerAcceleration, std::size_t maxHealth)
: BaseGameObject(x, y, w, h, playerAcceleration, maxHealth, 1)
{
}

void Player::Move() {
    Accelerate();
    auto renderSize = Game::GetSize();
    auto newX = _position.x + static_cast<int>(GetCurrentSpeed());
    if (newX <= 0 || newX + _position.w >= renderSize.x + renderSize.w) {
        return;
    } else {
        _position.x = newX;
    }
}


