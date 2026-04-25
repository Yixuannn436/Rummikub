#include "board.h"

void Board::addMeld(std::vector<Tile> meld) {
    melds.push_back(meld);
}

std::vector<std::vector<Tile>> Board::getTable() {
    return melds;
}

void Board::reset() {
    melds.clear();
}
