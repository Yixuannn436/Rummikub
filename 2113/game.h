#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "board.h"
#include "deck.h"
#include "player.h"
#include "ui.h"
#include "storage.h"
#include "validator.h"

class Game {
private:
    Board board;
    Deck deck;
    std::vector<Player*> players; // use base pointer for polymorphism
    UI ui;
    Storage storage;
    Validator validator;

    int turnIndex;
    bool isOver;

    // desc: do one turn
    // input: player pointer
    // output: none
    void doTurn(Player* player);

    // desc: print screen state
    // input: player pointer
    // output: none
    void showState(Player* player);

    // desc: move turn
    // input: none
    // output: none
    void nextPlayer();

public:
    // desc: setup game variables
    // input: none
    // output: none
    Game();

    // desc: delete players dynamic memory
    // input: none
    // output: none
    ~Game();

    // desc: menu for new or load game
    // input: none
    // output: none
    void startMenu(); 

    // desc: init game with 14 tiles per player
    // input: none
    // output: none
    void setup();

    // desc: main while loop
    // input: none
    // output: none
    void playLoop();

    // desc: check sudden death or empty deck
    // input: none
    // output: true if game is over
    bool checkWin();

    // desc: save and quit
    // input: none
    // output: none
    void saveAndQuit();
};

#endif