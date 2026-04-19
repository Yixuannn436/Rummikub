#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "tile.h"

class Board {
private:
    // 2d array for table
    std::vector<std::vector<Tile>> melds; 

public:
    // desc: put new valid meld on table
    // input: vector of tiles
    // output: none
    void addMeld(std::vector<Tile> meld);

    // desc: get all table melds
    // input: none
    // output: 2d vector
    std::vector<std::vector<Tile>> getTable();
    
    // desc: clear board
    // input: none
    // output: none
    void reset();
};

#endif