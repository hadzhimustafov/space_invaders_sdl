#ifndef BULLET_H
#define BULLET_H

#include "base_game_object.h"

class Bullet : public BaseGameObject
{
private:
    bool _isAliensBullet{false};
    std::size_t _id;

public:
    Bullet(std::size_t id, int x, int y, int w, int h);
    ~Bullet();
    [[nodiscard]] bool GetIsAlien() const { return _isAliensBullet; }
    void SetIsAlien(bool isAlien) { _isAliensBullet = isAlien; }
    [[nodiscard]] std::size_t GetId() const { return _id; }
};

#endif