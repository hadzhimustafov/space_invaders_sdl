#include "game_over_scene.h"
#include "../hud_manager.h"


GameOverScene::GameOverScene(Game *game, std::string username) : Scene(game), _username(std::move(username)) {
    _scoreManager = std::make_unique<ScoreManager>();
}

void GameOverScene::Load() {
    _scoreManager->Load();
    _scoreManager->Append(_username.c_str(), _game->GetScore());
    _scoreEntries = _scoreManager->GetTop(ScoreBoardPlaces);
}

void GameOverScene::OnDrawHud() const {
    auto hudManager = _game->GetHudManager();
    auto ren = _game->GetRenderer();

    hudManager->DrawText(ren, "Game Over", TITLE_X, TITLE_Y);

    for (int i = 1; i <= _scoreEntries.size(); i++) {
        auto entry = _scoreEntries[i-1];
        std::string scoreMessage{entry.name + " : " + std::to_string(entry.score)};
        hudManager->DrawText(ren, scoreMessage.c_str(), TITLE_X, TITLE_Y + (USERNAME_MARGIN * i));
    }

    hudManager->DrawText(ren, "Press ESC for cancel", TITLE_X, SCREEN_HEIGHT - TITLE_Y);
}