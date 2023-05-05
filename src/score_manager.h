#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <vector>
#include <string>
#include <istream>
#include <iostream>
#include "score_entry.h"

const std::string ScoreFilePath = "score.txt";


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

    [[nodiscard]] std::vector<ScoreEntry> GetTop(std::size_t n) const;
};

#endif
