#include <iostream>
#include "controller.h"
#include "scenes/scene.h"


void Controller::HandleKeyboardState(Scene &scene) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            scene.OnExit();
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    scene.OnExit();
                    break;
                case SDLK_LEFT:
                    scene.OnLeft();
                    break;
                case SDLK_RIGHT:
                    scene.OnRight();
                    break;
                case SDLK_SPACE:
                    scene.OnPlayerShoot();
                    break;
                default:
                    break;
            }
        } else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    scene.OnResetHorizontal();
                    break;
                default:
                    break;
            }
        }
    }
}

void Controller::HandleInput(Scene &scene) {
    HandleKeyboardState(scene);
    //todo: handle mouse position, controller, etc.
}

void Controller::HandleTextInput(std::string &name, const std::function<void()> &callback) {
    SDL_StartTextInput();
    bool isTyping{true};

    while (isTyping) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_TEXTINPUT:
                    name.append(e.text.text);
                    callback();
                    break;
                case SDL_KEYDOWN: {
                    switch (e.key.keysym.sym) {
                        case SDLK_BACKSPACE:
                            name.pop_back();
                            callback();
                            break;
                        case SDLK_RETURN:
                        case SDL_QUIT:
                            isTyping = false;
                            break;
                    }
                }
            }
        }
    }
    SDL_StopTextInput();
}