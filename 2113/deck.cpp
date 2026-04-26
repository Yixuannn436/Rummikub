#include "deck.h"
#include <algorithm>
#include <random>
#include <ctime>

// Constructor: create all 104 tiles (2 copies of 1-13 in 4 colors)
Deck::Deck() {
    // Two full sets of tiles
    for (int copy = 0; copy < 2; copy++) {
        // Four colors: RED, BLUE, YELLOW, BLACK
        for (int colorNum = 0; colorNum < 4; colorNum++) {
            Color color = static_cast<Color>(colorNum);
            // Numbers 1 to 13
            for (int num = 1; num <= 13; num++) {
                Tile* tile = new Tile;
                tile->number = num;
                tile->color = color;
                pool.push_back(tile);
            }
        }
    }
    // Shuffle after all tiles are created
    shuffle();
}

// Destructor: free all remaining tiles
Deck::~Deck() {
    for (Tile* tile : pool) {
        delete tile;
    }
    pool.clear();
}

// Shuffle the deck randomly
void Deck::shuffle() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::shuffle(pool.begin(), pool.end(), rng);
}

// Draw one tile from the top (end of vector)
// Return nullptr if deck is empty
Tile* Deck::draw() {
    if (isEmpty()) {
        return nullptr;
    }
    Tile* tile = pool.back();  // get last tile
    pool.pop_back();           // remove it from pool
    return tile;
}

// Check if deck has no tiles left
bool Deck::isEmpty() {
    return pool.empty();
}

// Return number of remaining tiles
int Deck::getSize() {
    return static_cast<int>(pool.size());
}
