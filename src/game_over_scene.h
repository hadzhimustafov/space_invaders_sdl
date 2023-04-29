#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include "scene.h"
#include "score_manager.h"

constexpr std::size_t ScoreBoardPlaces{10};

class GameOverScene : public Scene {
private:
    std::string _username;
    std::unique_ptr<ScoreManager> _scoreManager;
    std::vector<ScoreEntry> _scoreEntries;
public:
    GameOverScene(Game *game, std::string username);
    void Load() override;
    void OnDrawHud() const override;
};


#endif
