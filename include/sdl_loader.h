#ifndef SDL_LOADER_H
#define SDL_LOADER_H

#include "logger.h"

/// @brief Loads an image into a texture on the rendering device
/// @param file The BPM image path
/// @param ren The renderer to load the texture onto
/// @return the loaded texture, or nullptr if something went wrong
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren)
{
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr)
    {
        logSDLError(std::cout, "LoadTexture");
    }
    return texture;
}

#endif