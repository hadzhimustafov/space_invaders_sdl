#ifndef SCORE_ENTRY_H
#define SCORE_ENTRY_H

#include <iostream>
#include <istream>
#include <string>
#include <vector>

class ScoreEntry {
public:
    ScoreEntry(std::string name, size_t score) : name(std::move(name)), score(score) {}
    ScoreEntry(const ScoreEntry &entry) : name(entry.name), score(entry.score) {

    }
    ScoreEntry &operator=(const ScoreEntry &entry) {
        std::cout << "ScoreEntry assignment operator\n";
        if (this == &entry) {
            return *this;
        }
        name = entry.name;
        score = entry.score;
        return *this;
    }

    ScoreEntry(ScoreEntry &&entry) noexcept {
        std::cout << "ScoreEntry move ctor\n";
        name = std::move(entry.name);
        score = entry.score;
    }

    ScoreEntry &operator=(ScoreEntry &&entry) noexcept {
        std::cout << "ScoreEntry move assignment operator\n";
        if (this == &entry) {
            return *this;
        }
        name = std::move(entry.name);
        score = entry.score;
        return *this;
    }

    std::string name;
    size_t score;
};

#endif
