#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_TTF/SDL_ttf.h>
#include "scene.h"
#include "game.h"

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
    void Write(const ScoreEntry *entry);
    scoreList Read() const;
};


class GameOverScene : public Scene {
private:
    std::unique_ptr<ScoreManager> _scoreManager;
public:
    explicit GameOverScene(Game *game);
    void Load() override;
    void OnUpdate() override;
    void OnDraw() const override;
    void OnDrawHud(SDL_Color &color, TTF_Font *font) const override;
};


#endif
