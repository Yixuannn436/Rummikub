#ifndef AI_H
#define AI_H

#include "player.h"
#include "board.h"
#include "deck.h"

class AIPlayer : public Player {
private:
    int difficultyLevel; // 1 for easy, 2 for hard

public:
    // desc: setup ai player
    // input: name and difficulty level
    // output: none
    AIPlayer(std::string name, int difficultyLevel);

    // desc: ai logic for its turn
    // input: board reference, deck reference
    // output: none
    void playTurn(Board& board, Deck& deck);
};

#endif
