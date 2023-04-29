// #include <iostream>
// #include <string>
// #include <SDL2/SDL.h>
// #include <SDL2_image/SDL_image.h>
// #include "res_path.h"
// #include "cleanup.h"
#include "game.h"

// constexpr int TILE_SIZE = 40;
// const std::string LESSON = "Lesson3";





// /// @brief Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving the texture's width and height
// /// @param tex The source texture we want to draw
// /// @param _renderer The renderer we want to draw to
// /// @param x The x coordinate to draw to
// /// @param y The y coordinate to draw to
// /// @param w The width of texture to draw
// /// @param h The height of texture to draw
// void renderTexture(SDL_Texture *tex, SDL_Renderer *_renderer, int x, int y, int w, int h)
// {
//     // Setup the destination rectangle to be at the position we want
//     SDL_Rect dist;
//     dist.x = x;
//     dist.y = y;
//     dist.h = h;
//     dist.w = w;
//     SDL_RenderCopy(_renderer, tex, nullptr, &dist);
// }

// /// @brief Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving the texture's width and height
// /// @param tex The source texture we want to draw
// /// @param _renderer The renderer we want to draw to
// /// @param x The x coordinate to draw to
// /// @param y The y coordinate to draw to
// void renderTexture(SDL_Texture *tex, SDL_Renderer *_renderer, int x, int y)
// {
//     int w, h;
//     SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
//     renderTexture(tex, _renderer, x, y, w, h);
// }

// void render(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *image)
// {
//     // Clear the window
//     SDL_RenderClear(renderer);

//     //determine how many tiles we will
//     int xTiles = SCREEN_WIDTH / TILE_SIZE;
//     int yTiles = SCREEN_HEIGHT / TILE_SIZE;

//     //draw tiles by calculating their positions
//     for (size_t i = 0; i < xTiles * yTiles; ++i)
//     {
//         int x = i % xTiles; // Thus we can calculate the x index using the absolute tile index modded with the number of tiles per row: x = tile_idx % tiles_per_row.
//         int y = i / xTiles; // Since we’re using integers we can take advantage of integer truncation and compute this as y = tile_idx / tiles_per_row.
//         renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
//     }

//     // Draw our image in the center of the window
//     // We need the foreground image's width to properly compute the position
//     // of it's top left corner so that the image will be centered
//     int iW, iH;
//     SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
//     int x = SCREEN_WIDTH / 2 - iW / 2;
//     int y = SCREEN_HEIGHT / 2 - iH / 2;
//     renderTexture(image, renderer, x, y);

//     // Update the screen
//     SDL_RenderPresent(renderer);
// }

// int main(int, char **)
// {
//     if (SDL_Init(SDL_INIT_VIDEO) != 0)
//     {
//         logSDLError(std::cout, "SDL_Init");
//         return 1;
//     }

//     if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
//         logSDLError(std::cout, "IMG_INIT");
//         SDL_Quit();
//         return 1;
//     }

//     SDL_Window *window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//     if (window == nullptr)
//     {
//         logSDLError(std::cout, "SDL_CreateWindow");
//         SDL_Quit();
//         return 1;
//     }

//     SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if (renderer == nullptr)
//     {
//         cleanup(window);
//         logSDLError(std::cout, "SDL_CreateRenderer");
//         SDL_Quit();
//         return 1;
//     }
//     const std::string resPath = getResourcePath(LESSON);
//     SDL_Texture *background = loadTexture(resPath + "background.png", renderer);
//     SDL_Texture *image = loadTexture(resPath + "image.png", renderer);

//     if (background == nullptr || image == nullptr)
//     {
//         logSDLError(std::cout, "Images loading failed");
//         cleanup(background, image, renderer, window);
//         SDL_Quit();
//         IMG_Quit();
//         return 1;
//     }

//     render(renderer, background, image);

//     // A basic main loop to prevent blocking
//     bool is_running = true;
//     SDL_Event event;
//     while (is_running)
//     {
//         while (SDL_PollEvent(&event))
//         {
//             if (event.type == SDL_QUIT)
//             {
//                 is_running = false;
//             }
//         }
//         SDL_Delay(16);
//     }

//     cleanup(background, image, renderer, window);
//     SDL_Quit();
//     IMG_Quit(); 
//     return 0;
// }

int main(){
    Game g;
}