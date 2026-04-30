#include "deck.h"
#include <algorithm>
#include <random>
#include <ctime>

// desc: Constructor - create all 104 tiles (2 copies of 1-13 in 4 colors)
// input: none
// output: none
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

// desc: Destructor - free all remaining tiles
// input: none
// output: none
Deck::~Deck() {
    for (Tile* tile : pool) {
        delete tile;
    }
    pool.clear();
}

// desc: shuffle the deck randomly
// input: none
// output: none
void Deck::shuffle() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::shuffle(pool.begin(), pool.end(), rng);
}

// desc: draw one tile from the top (end of vector)
// input: none
// output: pointer to drawn tile, or nullptr if deck is empty
Tile* Deck::draw() {
    if (isEmpty()) {
        return nullptr;
    }
    Tile* tile = pool.back();  // get last tile
    pool.pop_back();           // remove it from pool
    return tile;
}

// desc: check if deck has no tiles left
// input: none
// output: true if empty, false otherwise
bool Deck::isEmpty() {
    return pool.empty();
}

// desc: return number of remaining tiles
// input: none
// output: count of tiles in deck
int Deck::getSize() {
    return static_cast<int>(pool.size());
}

// desc: get all remaining tiles in the deck
// input: none
// output: vector of tile pointers
std::vector<Tile*> Deck::getTiles() {
    return pool;
}

// desc: clear the deck memory when loading a new game
// input: none
// output: none
void Deck::clearDeck() {
    for (Tile* tile : pool) {
        delete tile;
    }
    pool.clear();
}

// desc: add a tile to the bottom of the deck for loading
// input: tile pointer
// output: none
void Deck::addTileToBottom(Tile* tile) {
    // Insert at beginning so draw() from back still works properly
    pool.insert(pool.begin(), tile);
}
