#include "game.h"
#include <iostream>
#include "cleanup.h"
#include "game_scene.h"
#include "game_over_scene.h"
#include "hud_manager.h"
#include "controller.h"
#include "logger.h"
#include "audio.h"

constexpr std::size_t SKIP_TICKS{0};

bool Game::TryLoadSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return false;
    }

    win = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        logSDLError(std::cout, "SDL_CreateWindow");
        return false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        logSDLError(std::cout, "SDL_CreateRenderer");
        return false;
    }
    return true;
}

Game::Game()
{
    _hudManager = std::make_unique<HudManager>();
    if(!TryLoadSDL() || !_hudManager->TryLoad()){
        return;
    }

    _running = true;

    _controllerPtr = std::make_unique<Controller>(this);
    _gameScenePtr = std::make_unique<GameScene>(this);
    _gameScenePtr->Load();

    _effectPtr = std::make_unique<Audio>();
    _effectPtr->Load("res/wav_example.wav");
    GameLoop();
}

Game::~Game()
{
    cleanup(ren, win);
    SDL_Quit();
}

void Game::GameLoop()
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    int ticksCounter=0;

    while (_running)
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

        Input();
        Update();
        Render();


        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000)
        {
            updateWindowTitle(frame_count);
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
}

void Game::Update()
{
    _gameScenePtr->OnUpdate();
}

void Game::updateWindowTitle(int fps)
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
//     int w, h;
//
//     if(SDL_GetRendererOutputSize(ren, &w, &h) != 0){
//         logSDLError(std::cout, "Unable to get renderer size");
//     };
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

void Game::GameOver()
{
    _gameOver = true;
    _gameScenePtr = std::make_unique<GameOverScene>(this);
    _gameScenePtr->Load();
}

void Game::Input()
{
    _controllerPtr->HandleInput();
}

void Game::Draw()
{
    _gameScenePtr->OnDraw();
    _gameScenePtr->OnDrawHud();
}

void Game::Exit() {
  _running = false;
}


