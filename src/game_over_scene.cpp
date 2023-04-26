#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include "game_over_scene.h"

GameOverScene::GameOverScene(Game *game): Scene(game) {
 _scoreManager = std::make_unique<ScoreManager>(ScoreFilePath);
}

void GameOverScene::Load() {
    auto scoreEntries = _scoreManager->Read();
    for (auto &&entry:scoreEntries) {

    }
}

void GameOverScene::OnUpdate() {

}

void GameOverScene::OnDraw() const {

}

void GameOverScene::OnDrawHud(SDL_Color &color, TTF_Font *font) const {
    auto ren =_game->GetRenderer();
    auto score = _game->GetScore();
    SDL_RenderClear(ren);

    // Draw the game over message
    SDL_Surface *gameOverSurface = TTF_RenderText_Solid(font, "Game Over", color);
    SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(ren, gameOverSurface);
    SDL_Rect gameOverRect = {static_cast<int>(SCREEN_WIDTH / 2) - gameOverSurface->w / 2,
                             static_cast<int>(SCREEN_HEIGHT / 2) - gameOverSurface->h / 2 - 50,
                             gameOverSurface->w,
                             gameOverSurface->h};
    SDL_RenderCopy(ren, gameOverTexture, nullptr, &gameOverRect);

    // Draw the score
    std::string scoreMessage{"Score: " + std::to_string(score)};
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreMessage.c_str(), color);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(ren, scoreSurface);
    SDL_Rect scoreRect = {static_cast<int>(SCREEN_WIDTH / 2) - scoreSurface->w / 2,
                          static_cast<int>(SCREEN_HEIGHT / 2) - scoreSurface->h / 2 + 50,
                          scoreSurface->w,
                          scoreSurface->h};
    SDL_RenderCopy(ren, scoreTexture, nullptr, &scoreRect);

    // Update the screen
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
}

ScoreManager::ScoreManager(std::string filename):_filename(std::move(filename)) {

}

ScoreManager::scoreList ScoreManager::Read() const {
    scoreList list;
    std::ifstream file(_filename);
    if(file){
        std::string line;
        while(getline(file, line)){
            // extract token type and info
            auto separatorPosition = line.find(':');
            if (separatorPosition != std::string::npos)
            {
                std::string name = line.substr(0, separatorPosition);
                std::string scoreStr = line.substr(separatorPosition + 1, line.size() - 1);
                std::size_t score = std::stol(scoreStr);
                // add token to vector
                list.emplace_back(std::make_pair(name, score));
            }
        }
    }
    return list;
}
