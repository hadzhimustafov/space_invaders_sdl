#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include "game_over_scene.h"

GameOverScene::GameOverScene(std::size_t score):_score(score) {
 _scoreManager = std::make_unique<ScoreManager>(ScoreFilePath);
}

void GameOverScene::Load() {
    auto scoreEntries = _scoreManager->Read();
    for (auto &&entry:scoreEntries) {

    }
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
