#include "player.h"
#include <iostream>

// Constructor: initialize player with empty hand
Player::Player(std::string playerName) 
    : name(playerName), handHead(nullptr), iceBroken(false) {}

// Destructor: free all tiles in hand
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

// Add a tile to player's hand (insert at head of linked list)
void Player::addTile(Tile* tile) {
    Node* newNode = new Node;
    newNode->tile = tile;
    newNode->next = handHead;
    handHead = newNode;
}

// Remove a tile by number and color (remove first match found)
// Return true if found and removed, false otherwise
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

// Calculate total value of all tiles in hand
int Player::getHandValue() {
    int total = 0;
    Node* current = handHead;
    while (current != nullptr) {
        total += current->tile->number;
        current = current->next;
    }
    return total;
}

// Check if player has broken the ice (score >= 30)
bool Player::isIceBroken() {
    return iceBroken;
}

// Set ice broken status
void Player::setIce(bool status) {
    iceBroken = status;
}

// Get head pointer of hand linked list
Node* Player::getHand() {
    return handHead;
}

// Get player name
std::string Player::getName() {
    return name;
}
