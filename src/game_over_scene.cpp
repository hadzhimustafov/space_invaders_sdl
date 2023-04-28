#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include "game_over_scene.h"
#include "game.h"
#include "controller.h"
#include "hud_manager.h"
#include "logger.h"

GameOverScene::GameOverScene(Game *game) : Scene(game) {
    _scoreManager = std::make_unique<ScoreManager>(ScoreFilePath);
}

void GameOverScene::Load() {
    auto userName = drawUserNameEnterScreen();
    auto scoreEntry = ScoreEntry{userName, _game->GetScore()};
    _scoreManager->Append(std::move(scoreEntry));
}

void GameOverScene::OnUpdate() {

}

void GameOverScene::OnDraw() const {

}

std::string GameOverScene::drawUserNameEnterScreen() const {

    //Get username
    auto hudManager = _game->GetHudManager();
    auto ren = _game->GetRenderer();
    if (SDL_RenderClear(ren) !=0 ){
        logSDLError(std::cout, "Clear screen failed");
    }
    hudManager->DrawText(ren,"Enter Name: ", TitleX, TitleY);
    auto userInputCallback = [&hudManager, &ren](const char * name){
        std::cout<<"********* Callback:" << name<<"\n";
        hudManager->DrawText(ren, name, TitleX,TitleY + UserNameMargin);
        SDL_RenderPresent(ren);
    };
    auto username = Controller::GetUserName(userInputCallback);
    return std::move(username);

    // Update the screen
//
}

void GameOverScene::OnDrawHud() const {
    //todo:
    //1: draw  game  over
    //2: draw user name
    //3: draw score table
    auto hudManager =_game->GetHudManager();
    auto ren = _game->GetRenderer();
    auto score = _game->GetScore();
    // Draw the game over message
    hudManager->DrawText(ren,"Game Over", TitleX, TitleY);

    // Draw the score
    std::string scoreMessage{"Score: " + std::to_string(score)};
    hudManager->DrawText(ren, scoreMessage.c_str(), TitleX, TitleY + UserNameMargin);
}

ScoreManager::ScoreManager(std::string filename) : _filename(std::move(filename)) {

}

ScoreManager::scoreList ScoreManager::Read() const {
    scoreList list;
    std::ifstream file(_filename);
    if (file) {
        std::string line;
        while (getline(file, line)) {
            // extract token type and info
            auto separatorPosition = line.find(':');
            if (separatorPosition != std::string::npos) {
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

void ScoreManager::Append(const ScoreEntry &&entry) {
    auto scoreList = Read();
    scoreList.emplace_back(std::make_pair(entry.name, entry.score));
    std::ofstream file(_filename);

    if (file.is_open()) {
        for (auto &&pair: scoreList) {
            file << pair.first << " : " << pair.second << std::endl;
        }
        file.close();
    } else {
        std::cout << "Failed to open file." << std::endl;
    }
}
