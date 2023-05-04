#ifndef ALIEN_H
#define ALIEN_H

#include <random>
#include "base_game_object.h"

class Alien : public BaseGameObject
{
private:
    int _shootTimer;
    std::size_t _id;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random;

public:
    Alien(std::size_t id, int x, int y, int w, int h) : BaseGameObject(x, y, w, h), _id(id), engine(dev()), random(300, 700) // todo: add maxShootInterval
    {
        _shootTimer = random(engine);
    }
    bool GetIfTimeToShoot();
    bool WillReachEdge(int leftEdge, int rightEdge);
    std::size_t GetId() const { return _id; }
    void Move();
    void ToggleDirection();
};

#endif