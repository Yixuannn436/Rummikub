#ifndef AI_H
#define AI_H

#include "player.h"
#include "board.h"
#include "deck.h"



class AIController {
public:
    // Difficulty 1：Easy mode (simple logic , ignore ice-breaking rules) 
    static bool playTurnEasy(PlayerHand& hand, std::vector<std::vector<Tile>>& board);

    // Difficulty 2：Hard mode (complex logic, checks ice-breaking rules; prioritize highest face value/most cards) 
    static bool playTurnHard(PlayerHand& hand, std::vector<std::vector<Tile>>& board, bool& iceBroken);
};



#endif
