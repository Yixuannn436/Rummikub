#include "player.h"
#include <iostream>

// desc: Constructor - initialize player with empty hand
// input: playerName - the name of the player
// output: none
Player::Player(std::string playerName) 
    : name(playerName), handHead(nullptr), iceBroken(false) {}

// desc: Destructor - free all tiles in hand
// input: none
// output: none
Player::~Player() {
    Node* current = handHead;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp->tile;
        delete temp;
    }
    handHead = nullptr;
}

// desc: Add a tile to player's hand (insert at head of linked list)
// input: tile - pointer to the tile to add
// output: none
void Player::addTile(Tile* tile) {
    Node* newNode = new Node;
    newNode->tile = tile;
    newNode->next = handHead;
    handHead = newNode;
}

// desc: Remove a tile by number and color (remove first match found)
// input: number - the number of the tile to remove, color - the color of the tile to remove
// output: true if found and removed, false otherwise
bool Player::removeTile(int number, Color color) {
    Node* prev = nullptr;
    Node* curr = handHead;
    
    while (curr != nullptr) {
        if (curr->tile->number == number && curr->tile->color == color) {
            if (prev == nullptr) {
                handHead = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr->tile;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

// desc: Calculate total value of all tiles in hand
// input: none
// output: sum of tile numbers in player's hand
int Player::getHandValue() {
    int total = 0;
    Node* current = handHead;
    while (current != nullptr) {
        total += current->tile->number;
        current = current->next;
    }
    return total;
}

// desc: Check if player has broken the ice (score >= 30)
// input: none
// output: true if ice is broken, false otherwise
bool Player::isIceBroken() {
    return iceBroken;
}

// desc: Set ice broken status
// input: status - new ice broken status (true/false)
// output: none
void Player::setIce(bool status) {
    iceBroken = status;
}

// desc: Get head pointer of hand linked list
// input: none
// output: pointer to the first Node in the hand linked list
Node* Player::getHand() {
    return handHead;
}

// desc: Get player name
// input: none
// output: player's name as string
std::string Player::getName() {
    return name;
}
