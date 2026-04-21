#include "deck.h"
#include <algorithm>
#include <random>
#include <ctime>

Deck::Deck() {
    for (int copy = 0; copy < 2; copy++) {
        for (int colorNum = 0; colorNum < 4; colorNum++) {
            Color color = static_cast<Color>(colorNum);
            for (int num = 1; num <= 13; num++) {
                Tile* tile = new Tile;
                tile->number = num;
                tile->color = color;
                pool.push_back(tile);
            }
        }
    }
    shuffle();
}

Deck::~Deck() {
    for (Tile* tile : pool) {
        delete tile;
    }
    pool.clear();
}

void Deck::shuffle() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::shuffle(pool.begin(), pool.end(), rng);
}

Tile* Deck::draw() {
    if (isEmpty()) {
        return nullptr;
    }
    Tile* tile = pool.back();
    pool.pop_back();
    return tile;
}

bool Deck::isEmpty() {
    return pool.empty();
}

int Deck::getSize() {
    return static_cast<int>(pool.size());
}
