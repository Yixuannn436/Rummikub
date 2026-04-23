#ifndef AI_H
#define AI_H

#include "player.h"
#include "board.h"
#include "deck.h"

class AIController {
public:
  
    static void playTurnEasy(Player& aiPlayer, Board& board, Deck& deck);
    static void playTurnHard(Player& aiPlayer, Board& board, Deck& deck);
};

#endif
