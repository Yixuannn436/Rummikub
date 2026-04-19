#ifndef TILE_H
#define TILE_H

// Four colors of a Rummikub tile
enum Color { RED, BLUE, YELLOW, BLACK };

// A single Rummikub tile, consisting of a number and a color
struct Tile {
    int number;  // 1 to 13
    Color color; 
};


 // Linked list node for player's hand
struct Node {
    Tile* tile;
    Node* next;
};

#endif