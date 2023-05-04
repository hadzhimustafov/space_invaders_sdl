#ifndef PLAYER_H
#define PLAYER_H

#include "base_game_object.h"

class Player : public BaseGameObject
{
public:
    Player(int x, int y, int w, int h, float playerAcceleration, std::size_t maxHealth);
    void Move();
};


#endif