#ifndef DECK_H
#define DECK_H

#include <vector>
#include "tile.h"

class Deck {
private:
    std::vector<Tile*> pool; 

public:
    // desc: create the 104 tiles
    // input: none
    // output: none
    Deck();

    // desc: delete left over tiles to prevent memory leak
    // input: none
    // output: none
    ~Deck();

    // desc: shuffle all tiles randomly
    // input: none
    // output: none
    void shuffle();

    // desc: get one tile from pool
    // input: none
    // output: tile pointer
    Tile* draw();
    
    // desc: is pool empty
    // input: none
    // output: true if zero left
    bool isEmpty();
    
    // desc: check how many left
    // input: none
    // output: integer count
    int getSize();
};

#endif