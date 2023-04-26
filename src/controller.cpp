#include "controller.h"
#include "player.h"
#include "game.h"
#include "game_scene.h"
#include <iostream>

void Controller::HandleKeyboardState(bool &running)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_w:
                    std::cout << "w down\n";
                    _game->PlaySound();
                    break;
                case SDLK_LEFT:
                    getCurrentScene()->OnLeft();
                    break;
                case SDLK_RIGHT:
                    getCurrentScene()->OnRight();
                    break;
                case SDLK_SPACE:
                    getCurrentScene()->OnPlayerShoot();
                    break;
                default:
                    break;
            }
        }
        else if (e.type == SDL_KEYUP)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_w:
                    std::cout << "w up\n";
                    break;
                case SDLK_LEFT:
                    getCurrentScene()->OnResetHorizontal();
                    break;
                case SDLK_RIGHT:
                    getCurrentScene()->OnResetHorizontal();
                    break;
                default:
                    break;
            }
        }
    }
}

void Controller::HandleMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    _game->UpdateMousePosition(x, y);
}

Scene *Controller::getCurrentScene()
{
    return _game->GetCurrentScene();
}

void Controller::HandleInput(bool &running)
{
    HandleKeyboardState(running);
    HandleMousePosition();
}