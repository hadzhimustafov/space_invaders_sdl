#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <vector>
#include <string>
#include <istream>
#include <iostream>

const std::string ScoreFilePath = "score.txt";

class ScoreEntry {
public:
    ScoreEntry(std::string name, std::size_t score) : name(std::move(name)), score(score) {} //1: ctor
    ScoreEntry(const ScoreEntry &entry) : name(entry.name), score(entry.score) {

    } // 2: copy ctor
    ScoreEntry &operator=(const ScoreEntry &entry) {   //3: copy assignment operator
        std::cout << "copy ctor\n";
        if (this == &entry) {
            return *this;
        }
        name = entry.name;
        score = entry.score;
        return *this;
    }

    ScoreEntry(ScoreEntry &&entry) noexcept { //4:move ctor
        std::cout << "move ctor\n";
        name = std::move(entry.name);
        score = entry.score;
    }

    ScoreEntry &operator=(ScoreEntry &&entry) noexcept { //5:move assignment operator
        if (this == &entry) {
            return *this;
        }
        name = std::move(entry.name);
        score = entry.score;
        return *this;
    }

    std::string name;
    std::size_t score;
};


class ScoreManager {
private:
    std::string _filename;
    std::vector<ScoreEntry> _entries{};
    std::vector<ScoreEntry> read();
    void write();

public:
    ScoreManager();

    void Load();

    void Append(const char *name, std::size_t score);

    std::vector<ScoreEntry> GetTop(std::size_t n) const;
};

#endif
