#ifndef CONTROLLER_H
#define CONTROLLER_H


class Player;//forward declaration
class Game;//forward declaration
class GameScene; //forward declaration

class Controller
{
private:
    //not owned
    Game *_game;

    void HandleKeboardState(bool &running);
    void HandleMousePosition();
    GameScene *getCurrentScene();

public:
    Controller(Game *game):_game(game){}
    // ~Controller();
    void HandleInput(bool &running);
    
};

#endif