#ifndef UI_H
#define UI_H

#include "tile.h"

class UI {
public:
    // desc: print a welcome message and the game title to the console
    // input: none
    // output: none
    static void printWelcome();

    // desc: prompt the user for an integer input and validate it within a range
    // input: min (minimum allowed value), max (maximum allowed value)
    // output: the validated integer
    static int getValidInt(int min, int max);

    // desc: display a single game tile with its specific color and number
    // input: t (the tile object to be displayed)
    // output: none
    static void displayTile(const Tile& t);

    // desc: clear the terminal screen using ANSI escape sequences
    // input: none
    // output: none
    static void clearScreen();
};

#endif
