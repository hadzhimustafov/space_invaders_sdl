#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game.h"

class Player;//forward declaration
class Scene; //forward declaration

class Controller
{
private:
    //not owned
    Game *_game;

    void HandleKeyboardState();
    void HandleMousePosition();
    Scene *getCurrentScene();
    static void handleTextInputEvent(const SDL_TextInputEvent& e, std::string &userName);

public:
    Controller(Game *game):_game(game){}
    // ~Controller();
    static std::string GetUserName(const std::function<void(const char*)>& callback);
    void HandleInput();
};

#endif