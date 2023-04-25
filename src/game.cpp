#include "game.h"
#include <iostream>
#include "cleanup.h"
#include "game_scene.h"
#include "controller.h"
#include "logger.h"
#include "audio.h"

constexpr std::size_t SKIP_TICKS{0};

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
    }

    if (TTF_Init() != 0)
    {
        logSDLError(std::cout, "TTF_Init");
        SDL_Quit();
    }

    win = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        logSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit();
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        cleanup(win);
        logSDLError(std::cout, "SDL_CreateRenderer");
        SDL_Quit();
    }

    _running = true;

    _controllerPtr = std::make_unique<Controller>(this);

    _gameScenePtr = std::make_unique<GameScene>(this);
    _gameScenePtr->Load();
    font = TTF_OpenFont("res/kenvector_future.ttf", FONT_SIZE);
    _effectPtr = std::make_unique<Audio>();
    _effectPtr->Load("res/wav_example.wav");
    GameLoop();
}

Game::~Game()
{
    cleanup(ren, win);
    SDL_Quit();
    TTF_Quit();
}

void Game::GameLoop()
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    int ticksCounter=0;

    while (_running && !_gameOver)
    {
        lastFrame = frame_start = SDL_GetTicks();
        // todo: game speed
        // if(ticksCounter >  SKIP_TICKS){
        //     ticksCounter = 0;
        //     Render();
        //     Input();
        //     Update();
        // }else{
        //     ticksCounter++;
        // }

        Render();
        Input();
        Update();

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000)
        {
            UpdateWindowTitle(frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < MsPerFrame)
        {
            SDL_Delay(MsPerFrame - frame_duration);
        }
    }
//    if (_running && _gameOver)
//    {
//        while (_running)
//        {
//            drawGameOverScreen();
//            Input();
//        }
//    }
}

void Game::Update()
{
    _gameScenePtr->OnUpdate();
}

void Game::UpdateWindowTitle(int fps)
{
    std::string title{"Score: " + std::to_string(_score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(win, title.c_str());
}

void Game::Render()
{
    //clear screen
    SDL_RenderClear(ren);
//    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);

    //Draw  Game Objects
    Draw();

    //Render  drawings
    SDL_RenderPresent(ren);
}

SDL_Rect Game::GetSize() const
{
    // int w, h;

    // if(SDL_GetRendererOutputSize(ren, &w, &h) != 0){
    //     logSDLError(std::cout, "Unable to get renderer size");
    // };
    return SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Game::UpdateMousePosition(int x, int y)
{
    mouseX = x;
    mouseY = y;
}

void Game::PlaySound() const
{
    _effectPtr->Play();
}

GameScene *Game::GetCurrentScene() const
{
    return _gameScenePtr.get();
}

void Game::GameOver()
{
    _gameOver = true;
}

void Game::Input()
{
    _controllerPtr->HandleInput(_running);
}

void Game::Draw()
{
    _gameScenePtr->OnDraw();
    _gameScenePtr->OnDrawHud(color, font);
}


void Game::drawGameOverScreen()
{
    SDL_RenderClear(ren);

    // Draw the game over message
    SDL_Surface *gameOverSurface = TTF_RenderText_Solid(font, "Game Over", color);
    SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(ren, gameOverSurface);
    SDL_Rect gameOverRect = {static_cast<int>(SCREEN_WIDTH / 2) - gameOverSurface->w / 2,
                             static_cast<int>(SCREEN_HEIGHT / 2) - gameOverSurface->h / 2 - 50,
                             gameOverSurface->w,
                             gameOverSurface->h};
    SDL_RenderCopy(ren, gameOverTexture, NULL, &gameOverRect);

    // Draw the score
    std::string scoreMessage{"Score: " + std::to_string(_score)};
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreMessage.c_str(), color);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(ren, scoreSurface);
    SDL_Rect scoreRect = {static_cast<int>(SCREEN_WIDTH / 2) - scoreSurface->w / 2,
                          static_cast<int>(SCREEN_HEIGHT / 2) - scoreSurface->h / 2 + 50,
                          scoreSurface->w,
                          scoreSurface->h};
    SDL_RenderCopy(ren, scoreTexture, NULL, &scoreRect);

    // Update the screen
    SDL_RenderPresent(ren);
}
