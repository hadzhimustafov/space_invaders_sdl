#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_TTF/SDL_ttf.h>
#include "scene.h"

constexpr int TitleX{50};
constexpr int TitleY{50};
constexpr int UserNameMargin{50};
constexpr int UserNameWidth{100};
constexpr int UserNameHeight{30};

const std::string ScoreFilePath = "score.txt";

struct ScoreEntry{
    std::string name;
    std::size_t score;
};

class ScoreManager{
private:
    std::string _filename;
public:
    typedef std::vector<std::pair<std::string, std::size_t>> scoreList;
    ScoreManager(std::string filename);
    void Append(const ScoreEntry &&entry);
    scoreList Read() const;
};

class GameOverScene : public Scene {
private:
    std::unique_ptr<ScoreManager> _scoreManager;
    std::string drawUserNameEnterScreen() const;
public:
    explicit GameOverScene(Game *game);
    void Load() override;
    void OnUpdate() override;
    void OnDraw() const override;
    void OnDrawHud() const override;

};


#endif
