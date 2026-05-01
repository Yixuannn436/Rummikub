#ifndef AI_H
#define AI_H

#include "player.h"
#include "board.h"
#include "deck.h"

class AIPlayer : public Player {
private:
    int difficultyLevel; // 1 for easy, 2 for hard

public:
     // desc: initializes an AIPlayer object with a specified name and difficulty level
    // input: name (string) representing the player's name, difficultyLevel (int) for the AI strategy
    // output: none
    AIPlayer(std::string name, int difficultyLevel);

    // desc: ai logic for its turn
    // input: board reference, deck reference
    // output: none
    void playTurn(Board& board, Deck& deck);
};

#endif
