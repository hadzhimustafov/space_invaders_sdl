#ifndef SCENE_H
#define SCENE_H

#include <SDL2_TTF/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>

class Scene {

public:
    virtual void Load() = 0;

    virtual void OnUpdate() = 0;

    virtual void OnDraw() const = 0;

    virtual void OnDrawHud(SDL_Color &color, TTF_Font *font) const = 0;
};


#endif
