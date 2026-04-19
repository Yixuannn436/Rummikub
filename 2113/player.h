#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "tile.h"

class Player {
protected:
    std::string name;
    Node* handHead; // pointer to linked list
    bool iceBroken;

public:
    // desc: setup new player
    // input: player name string
    // output: none
    Player(std::string playerName);

    // desc: clean up hand memory
    // input: none
    // output: none
    virtual ~Player();

    // desc: put drawn tile into hand
    // input: tile pointer
    // output: none
    void addTile(Tile* tile);

    // desc: drop a tile when playing it
    // input: number and color
    // output: true if drop is successful
    bool removeTile(int number, Color color);

    // desc: get penalty score at end game
    // input: none
    // output: sum of tile numbers
    int getHandValue();

    // desc: check 30 points rule status
    // input: none
    // output: true if broken
    bool isIceBroken();

    // desc: update ice status
    // input: boolean status
    // output: none
    void setIce(bool status);

    // desc: get hand linked list for user interface
    // input: none
    // output: pointer to first node
    Node* getHand();
    
    // desc: return name
    // input: none
    // output: string name
    std::string getName();
};

#endif