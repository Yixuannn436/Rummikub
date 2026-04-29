#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include "player.h"
#include "board.h"
#include "deck.h"

class Storage {
public:
    // desc: save game state to a text file
    // input: filename, players list, deck, board, current turn
    // output: true if file is saved successfully, false otherwise
    static bool saveGame(std::string filename, const std::vector<Player*>& players, Deck& deck, Board& board, int currentTurn);

    // desc: load game state from a text file
    // input: filename, players list, deck, board, current turn reference
    // output: true if file is loaded successfully, false otherwise
    static bool loadGame(std::string filename, std::vector<Player*>& players, Deck& deck, Board& board, int& currentTurn);
};

#endif
