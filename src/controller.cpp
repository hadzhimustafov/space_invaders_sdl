#include "controller.h"
#include "player.h"
#include "game_scene.h"
#include <iostream>

void Controller::HandleKeyboardState()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            _game->Exit();
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    _game->Exit();
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

void Controller::HandleInput()
{
    HandleKeyboardState();
    HandleMousePosition();
}

void Controller::handleTextInputEvent(const SDL_TextInputEvent &e, std::string &userName) {
    // Check if the input is a valid character (ASCII 32-126).
    if ((e.text[0] >= 32) && (e.text[0] <= 126)) {
        userName += e.text;
    }
}

std::string Controller::GetUserName(const std::function<void(const char*)>& callback) {
    SDL_StartTextInput();
    std::string userName;
    bool isTyping{true};

    while (isTyping) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            std::cout << e.type << "\n";
            switch (e.type) {
                case SDL_TEXTINPUT:
                    handleTextInputEvent(e.text, userName);
                    callback(userName.c_str());
                    break;
                case SDL_KEYDOWN:{
                    switch (e.key.keysym.sym){
                        //todo: handle backspace
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
    return std::move(userName);
}