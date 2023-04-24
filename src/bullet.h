#ifndef BULLET_H
#define BULLET_H

#include "base_game_object.h"

class Bullet : public BaseGameObject
{
private:
    /* data */
    bool _isAliensBullet;
    std::size_t _id;

public:
    Bullet(std::size_t id, int x, int y, int w, int h);
    ~Bullet();
    bool GetIsAlien() const { return _isAliensBullet; }
    void SetIsAlien(bool isAlien) { _isAliensBullet = isAlien; }
    std::size_t GetId() const { return _id; }
};

#endif