#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <SDL2/SDL.h>
#if defined(macintosh) || defined(Macintosh) || defined(__APPLE__)
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

class Controller; // forward declaration
class Scene;  // forward declaration
class HudManager;  // forward declaration

constexpr std::size_t FramesPerSecond{60};
constexpr std::size_t MsPerFrame{1000 / FramesPerSecond};
constexpr int SCREEN_WIDTH{1280};
constexpr int SCREEN_HEIGHT{720};
constexpr int OBSTACLE_POSITION{500};
constexpr std::size_t FONT_SIZE{32};
const std::string WINDOW_TITLE{"Space Invaders"};
constexpr int TITLE_X{50};
constexpr int TITLE_Y{50};
constexpr int USERNAME_MARGIN{50};

class Game {
public:
    Game();

    ~Game();

    [[nodiscard]] std::size_t GetScore() const { return _score; }

    void SetScore(std::size_t score) { _score = score; }

    [[nodiscard]] static SDL_Rect GetSize();

    [[nodiscard]] SDL_Renderer *GetRenderer() const { return _renderer; }

    [[nodiscard]] HudManager *GetHudManager() const { return _hudManager.get(); }

    void GameOver();

    void Exit();

private:
    //owned resources
    SDL_Renderer *_renderer{};
    SDL_Window *_window{};

    bool _running{false};
    std::size_t _score{0};
    std::string _username;
    std::shared_ptr<Controller> _controller;
    std::unique_ptr<Scene> _currentScene;
    std::unique_ptr<HudManager> _hudManager;
    //not owned resources

    bool TryLoadSDL();

    void GameLoop();

    void Update();

    void Input();

    void Render();

    void updateWindowTitle(int fps);

    std::string getUserName();

};

#endif