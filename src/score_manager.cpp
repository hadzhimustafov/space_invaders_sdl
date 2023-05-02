#include <fstream>

#include <utility>
#include <algorithm>
#include "score_manager.h"

ScoreManager::ScoreManager() : _filename(ScoreFilePath) {

}

void ScoreManager::Load() {
    _entries = read();
}

std::vector<ScoreEntry> ScoreManager::read() {
    std::vector<ScoreEntry> entries;
    std::ifstream file(_filename);
    if (file) {
        std::string line;
        while (getline(file, line)) {
            auto separatorPosition = line.find(':');
            if (separatorPosition != std::string::npos) {
                std::string name = line.substr(0, separatorPosition);
                std::string scoreStr = line.substr(separatorPosition + 1, line.size() - 1);
                std::size_t score = std::stol(scoreStr);
                entries.emplace_back(std::move(name), score);
            }
        }
    }else {
        std::cout << "Failed to open file: " << _filename << std::endl;
    }
    return entries;
}

void ScoreManager::Append(const char *name, std::size_t score) {
    _entries.emplace_back(name, score);
    std::sort(_entries.begin(), _entries.end(), [](ScoreEntry &a, ScoreEntry &b) { return a.score > b.score; });
    write();
}

void ScoreManager::write() {
    std::ofstream file(_filename);
    if (file.is_open()) {
        for (auto &&entry: _entries) {
            file << entry.name << ":" << entry.score << std::endl;
        }
        file.close();
    } else {
        std::cout << "Failed to open file: " << _filename << std::endl;
    }
}

std::vector<ScoreEntry> ScoreManager::GetTop(std::size_t n) const {
    std::vector<ScoreEntry> topN;
    auto min = std::min(n, _entries.size());
    topN.reserve(min);
    for (auto i = 0; i < min; ++i) {
        topN.emplace_back(_entries[i]);
    }
    return topN;
}
