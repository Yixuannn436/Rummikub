#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include "tile.h"

class Validator {
private:
    // desc: check run (consecutive numbers, same color)
    // input: tile vector
    // output: true if valid
    bool checkRun(std::vector<Tile> meld);

    // desc: check group (same number, different colors)
    // input: tile vector
    // output: true if valid
    bool checkGroup(std::vector<Tile> meld);

public:
    // desc: main checker for any meld
    // input: tile vector
    // output: boolean valid
    bool isValid(std::vector<Tile> meld);

    // desc: get score for ice break
    // input: tile vector
    // output: integer total score
    int sumScore(std::vector<Tile> meld);
};

#endif