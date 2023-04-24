#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2_IMAGE/SDL_image.h>
#include <SDL2_TTF/SDL_ttf.h>

class Audio;      // forward declaration
class Controller; // forward declaration
class GameScene;  // forward declaration

constexpr std::size_t FramesPerSecond{60};
constexpr std::size_t MsPerFrame{1000 / FramesPerSecond};
constexpr std::size_t SCREEN_WIDTH{1280};
constexpr std::size_t SCREEN_HEIGHT{720};
constexpr std::size_t OBSTACLE_POSITION{500};
constexpr std::size_t FONT_SIZE{32};

class Game
{
public:
    Game();
    ~Game();
   
    int GetScore() const { return _score; }
    void SetScore(int score) { _score = score; }
    SDL_Rect GetSize() const;
    void UpdateMousePosition(int x, int y);
    void PlaySound() const;
    GameScene *GetCurrentScene() const;
    SDL_Renderer *GetRenderer() const { return ren; }
    void GameOver();
private:
    //owned resources
    SDL_Renderer *ren;
    SDL_Window *win;
    TTF_Font *font;
    SDL_Color color = {255, 255, 255, 255};
    bool _running{false}, _gameOver{false};
    int frameCount, timerFps, lastFrame;
    int mouseX, mouseY;
    int _score{0};
    std::unique_ptr<Audio> _effectPtr;
    std::unique_ptr<Controller> _controllerPtr;
    std::unique_ptr<GameScene> _gameScenePtr;
    //not owned resources

    void GameLoop();
    void Update();
    void Input();
    void Render();
    void Draw();
    void drawGameOverScreen();
    void UpdateWindowTitle(int fps);
};

#endif