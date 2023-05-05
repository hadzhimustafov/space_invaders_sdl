#include <iostream>
#include "obstacle.h"
#include "logger.h"

Obstacle::Obstacle(std::size_t id, int x, int y, int w, int h, int maxHealth)
: BaseGameObject(x, y, w, h, 0, maxHealth, 1), _id(id)
{
}

void Obstacle::Draw(SDL_Renderer *ren) const{
    auto spriteFrame = _health > 1 ? &_solidSprite : &_damagedSprite;

    if(SDL_RenderCopyEx(ren, tex, spriteFrame, &_position, 0, nullptr, SDL_FLIP_NONE) != 0){
        logSDLError(std::cout, "render metal block failed");
    }
}