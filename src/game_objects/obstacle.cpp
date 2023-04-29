#include <iostream>
#include "obstacle.h"
#include "logger.h"

void Obstacle::Draw(SDL_Renderer *ren) const{
    auto _spriteFrame = _health > 1 ?&_solidSprite : &_damagedSprite;

    if(SDL_RenderCopyEx(ren, tex, _spriteFrame, &_position, 0, nullptr, SDL_FLIP_NONE) != 0){
        logSDLError(std::cout, "render metal block failed");
    };
}