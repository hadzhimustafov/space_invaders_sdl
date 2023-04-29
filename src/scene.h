#ifndef SCENE_H
#define SCENE_H

#include <SDL2_TTF/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include "game.h"

class Scene {
protected:
    Game *_game;
public:
    explicit Scene(Game *game) : _game(game) {}

    virtual ~Scene() = default;

    virtual void Load() = 0;

    virtual void OnUpdate() {}

    virtual void OnDraw() const {}

    virtual void OnDrawHud() const {}

    virtual void OnLeft() {}

    virtual void OnRight() {}

    virtual void OnResetHorizontal() {}

    virtual void OnPlayerShoot() {}

    virtual void OnExit() const {
        _game->Exit();
    }
};


#endif
