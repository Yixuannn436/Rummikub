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

    // desc: executes the AI's turn, playing a valid meld to the board based on difficulty level, or drawing a tile if no melds are possible
   // input: board (reference to the game Board), deck (reference to the game Deck)
  // output: none (modifies game state directly)
    void playTurn(Board& board, Deck& deck);
};

#endif
