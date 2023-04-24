#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "base_game_object.h"


class Obstacle : public BaseGameObject
{
private:
    std::size_t _id;
    SDL_Rect _solidSprite{35,52, 24,24};
    SDL_Rect _damagedSprite{35, 75, 24, 24};
public:
    Obstacle(std::size_t id, int x, int y, int w, int h, int maxHealth = 2) : BaseGameObject(x, y, w, h, 0, maxHealth, 1), _id(id) {}
    std::size_t GetId() const {return _id;}

    void Draw(SDL_Renderer *ren) const override;
};

#endif