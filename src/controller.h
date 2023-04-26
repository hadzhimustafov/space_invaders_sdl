#ifndef CONTROLLER_H
#define CONTROLLER_H


class Player;//forward declaration
class Game;//forward declaration
class Scene; //forward declaration

class Controller
{
private:
    //not owned
    Game *_game;

    void HandleKeyboardState(bool &running);
    void HandleMousePosition();
    Scene *getCurrentScene();

public:
    Controller(Game *game):_game(game){}
    // ~Controller();
    void HandleInput(bool &running);
    
};

#endif