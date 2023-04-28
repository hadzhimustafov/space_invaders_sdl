#ifndef HUDMANAGER_H
#define HUDMANAGER_H

#include <iostream>
#include "game.h"
#include "cleanup.h"

class HudManager {
private:
    //owned
    TTF_Font *_font{};
    SDL_Color color = {255, 255, 255, 255};

public:

    ~HudManager(){
        std::cout << "HUD manager destructor started \n";
        cleanup(_font);
        std::cout << "HUD manager destructor finished \n";
        TTF_Quit();
    }
    bool TryLoad();
    void DrawText(SDL_Renderer *ren, const char* text, int x, int  y) const;
};


#endif
