#include "hud_manager.h"
#include "cleanup.h"
#include "logger.h"

bool HudManager::TryLoad() {
    if (TTF_Init() != 0)
    {
        logSDLError(std::cout, "TTF_Init");
        return false;
    }
    _font = TTF_OpenFont("res/kenvector_future.ttf", FONT_SIZE);
    return true;
}

void HudManager::DrawText(SDL_Renderer *ren,const char *text, int x, int y) const {
    SDL_Surface *surface = TTF_RenderText_Solid(_font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_Rect position{x, y, surface->w, surface->h};
    SDL_RenderCopy(ren, texture, nullptr, &position);
    cleanup(surface, texture);
}