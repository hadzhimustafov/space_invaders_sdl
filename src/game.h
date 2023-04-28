#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2_IMAGE/SDL_image.h>
#include <SDL2_TTF/SDL_ttf.h>

class Audio;      // forward declaration
class Controller; // forward declaration
class Scene;  // forward declaration
class HudManager;  // forward declaration

constexpr std::size_t FramesPerSecond{60};
constexpr std::size_t MsPerFrame{1000 / FramesPerSecond};
constexpr std::size_t SCREEN_WIDTH{1280};
constexpr std::size_t SCREEN_HEIGHT{720};
constexpr std::size_t OBSTACLE_POSITION{500};
constexpr std::size_t FONT_SIZE{32};
const std::string WINDOW_TITLE{"Space Invaders"};

class Game
{
public:
    Game();
    ~Game();
   
    [[nodiscard]] std::size_t GetScore() const { return _score; }
    void SetScore(std::size_t score) { _score = score; }
    [[nodiscard]] SDL_Rect GetSize() const;
    void UpdateMousePosition(int x, int y);
    void PlaySound() const;
    [[nodiscard]] Scene *GetCurrentScene() const{return _gameScenePtr.get();}
    [[nodiscard]] SDL_Renderer *GetRenderer() const { return ren; }
    [[nodiscard]] Controller *GetController() const { return _controllerPtr.get();}
    [[nodiscard]] HudManager *GetHudManager() const {return _hudManager.get(); }
    void GameOver();
    void Exit();
private:
    //owned resources
    SDL_Renderer *ren;
    SDL_Window *win;

    bool _running{false}, _gameOver{false};
    int frameCount, timerFps, lastFrame;
    int mouseX, mouseY;
    std::size_t _score{0};
    std::unique_ptr<Audio> _effectPtr;
    std::shared_ptr<Controller> _controllerPtr;
    std::unique_ptr<Scene> _gameScenePtr;
    std::unique_ptr<HudManager>_hudManager;
    //not owned resources

    bool TryLoadSDL();
    void GameLoop();
    void Update();
    void Input();
    void Render();
    void Draw();
    void updateWindowTitle(int fps);

};

#endif