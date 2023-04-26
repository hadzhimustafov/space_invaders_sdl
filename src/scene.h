#ifndef SCENE_H
#define SCENE_H

#include <SDL2_TTF/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include "game.h"

class Scene {
protected:
    Game * _game;
public:
    explicit Scene(Game *game) : _game(game){ }
    virtual ~Scene(){

    }

    virtual void Load() = 0;

    virtual void OnUpdate() = 0;

    virtual void OnDraw() const = 0;

    virtual void OnDrawHud(SDL_Color &color, TTF_Font *font) const = 0;

    virtual void OnLeft(){

    }

    virtual void OnRight(){

    }

    virtual void OnResetHorizontal(){

    }

    virtual void OnPlayerShoot(){

    }
};


#endif
