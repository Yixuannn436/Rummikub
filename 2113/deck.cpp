#include "deck.h"
#include <algorithm>
#include <random>
#include <ctime>

// Constructor: create 104 tiles (2 copies x 4 colors x 1-13)
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

// Destructor: free all tiles
Deck::~Deck() {
    for (Tile* tile : pool) {
        delete tile;
    }
    pool.clear();
}

// Shuffle deck randomly
void Deck::shuffle() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::shuffle(pool.begin(), pool.end(), rng);
}

// Draw one tile from top (end of vector)
Tile* Deck::draw() {
    if (isEmpty()) return nullptr;
    Tile* tile = pool.back();
    pool.pop_back();
    return tile;
}

// Check if deck is empty
bool Deck::isEmpty() {
    return pool.empty();
}

// Return number of remaining tiles
int Deck::getSize() {
    return static_cast<int>(pool.size());
}

// Get all tiles (for save/load)
std::vector<Tile*> Deck::getTiles() {
    return pool;
}

// Clear all tiles (for loading new game)
void Deck::clearDeck() {
    for (Tile* tile : pool) {
        delete tile;
    }
    pool.clear();
}

// Add tile to bottom (for loading)
void Deck::addTileToBottom(Tile* tile) {
    pool.insert(pool.begin(), tile);
}
