#include "game.h"
#include <iostream>
#include "cleanup.h"
#include "scenes/game_scene.h"
#include "scenes/game_over_scene.h"
#include "hud_manager.h"
#include "controller.h"
#include "logger.h"

bool Game::TryLoadSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cout, "SDL_Init");
        return false;
    }

    _window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        logSDLError(std::cout, "SDL_CreateWindow");
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr) {
        logSDLError(std::cout, "SDL_CreateRenderer");
        return false;
    }
    return true;
}

Game::Game() {
    _hudManager = std::make_unique<HudManager>();
    if (!TryLoadSDL() || !_hudManager->TryLoad()) {
        return;
    }

    _username = getUserName();
    if(_username.empty()) return;
    _running = true;

    _controller = std::make_unique<Controller>();
    _currentScene = std::make_unique<GameScene>(this);
    _currentScene->Load();

    GameLoop();
}

Game::~Game() {
    cleanup(_renderer, _window);
    SDL_Quit();
}

void Game::GameLoop() {

    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    while (_running) {
        frame_start = SDL_GetTicks();

        Input();
        Update();
        Render();


        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            updateWindowTitle(frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < MsPerFrame) {
            SDL_Delay(MsPerFrame - frame_duration);
        }
    }
}

void Game::Update() {
    _currentScene->OnUpdate();
}

void Game::updateWindowTitle(int fps) {
    std::string title{WINDOW_TITLE + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(_window, title.c_str());
}

void Game::Render() {
    //clear screen
    SDL_RenderClear(_renderer);

    //Draw Game Objects
    _currentScene->OnDraw();
    _currentScene->OnDrawHud();

    //Render  drawings
    SDL_RenderPresent(_renderer);
}

SDL_Rect Game::GetSize() {
    return SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}


void Game::GameOver() {
    _currentScene = std::make_unique<GameOverScene>(this, _username);
    _currentScene->Load();
}

void Game::Input() {
    _controller->HandleInput(*_currentScene);
}

void Game::Exit() {
    _running = false;
}

std::string Game::getUserName() {
    std::string username{};
    SDL_RenderClear(_renderer);
    _hudManager->DrawText(_renderer,"Enter Name: ", TITLE_X, TITLE_Y);
    _hudManager->DrawText(_renderer, "Press <ENTER> to confirm or <ESC> to cancel", TITLE_X, SCREEN_HEIGHT - TITLE_Y);
    SDL_RenderPresent(_renderer);

    auto userInputCallback = [this, &username](){
        SDL_RenderClear(_renderer);
        _hudManager->DrawText(_renderer,"Enter Name: ", TITLE_X, TITLE_Y);
        _hudManager->DrawText(_renderer, username.c_str(), TITLE_X,TITLE_Y + USERNAME_MARGIN);
        SDL_RenderPresent(_renderer);
    };

    Controller::HandleTextInput(username, userInputCallback);
    return std::move(username);
}


