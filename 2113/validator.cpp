#include "validator.h"
#include <algorithm>
#include <set>

bool compareTiles(const Tile& a, const Tile& b) {
    return a.number < b.number;
}

bool Validator::checkRun(std::vector<Tile> meld) {
    if (meld.size() < 3) {
        return false;
    }
    
    std::vector<Tile> sortedMeld = meld;
    std::sort(sortedMeld.begin(), sortedMeld.end(), compareTiles);
    
    auto firstColor = sortedMeld[0].color;
    
    for (size_t i = 0; i < sortedMeld.size(); ++i) {
        if (sortedMeld[i].color != firstColor) {
            return false;
        }
        if (i > 0 && sortedMeld[i].number != sortedMeld[i-1].number + 1) {
            return false;
        }
    }
    return true;
}

bool Validator::checkGroup(std::vector<Tile> meld) {
    if (meld.size() < 3 || meld.size() > 4) {
        return false;
    }
    
    int firstNumber = meld[0].number;
    std::set<int> colors;
    
    for (const auto& tile : meld) {
        if (tile.number != firstNumber) {
            return false;
        }
        colors.insert(static_cast<int>(tile.color));
    }
    
    return colors.size() == meld.size();
}

bool Validator::isValid(std::vector<Tile> meld) {
    return checkRun(meld) || checkGroup(meld);
}

int Validator::sumScore(std::vector<Tile> meld) {
    int score = 0;
    for (const auto& tile : meld) {
        score += tile.number;
    }
    return score;
}
