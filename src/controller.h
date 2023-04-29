#ifndef CONTROLLER_H
#define CONTROLLER_H

class Scene; //forward declaration

class Controller {
private:
    static void HandleKeyboardState(Scene &scene);

public:
    static void HandleTextInput(std::string &name, const std::function<void()>& callback);

    static void HandleInput(Scene &scene);
};

#endif