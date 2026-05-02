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

// Add a tile to player's hand (Sorted Insert)
// Primary sort: by Color (RED, BLUE, YELLOW, BLACK)
// Secondary sort: by Number (1 to 13)
void Player::addTile(Tile* tile) {
    Node* newNode = new Node();
    newNode->tile = tile;
    newNode->next = nullptr;

    // Case 1: Empty list or new tile should be at the head
    if (handHead == nullptr || 
        (tile->color < handHead->tile->color) || 
        (tile->color == handHead->tile->color && tile->number < handHead->tile->number)) {
        
        newNode->next = handHead;
        handHead = newNode;
        return;
    }

    // Case 2: Traverse to find the correct sorted position
    Node* current = handHead;
    while (current->next != nullptr) {
        Tile* nextTile = current->next->tile;
        
        // Stop if the next tile is greater than our new tile
        if ((tile->color < nextTile->color) || 
            (tile->color == nextTile->color && tile->number < nextTile->number)) {
            break;
        }
        current = current->next;
    }

    // Insert the new node after 'current'
    newNode->next = current->next;
    current->next = newNode;
}

// Remove a tile by number and color (remove first match found)
// Return true if found and removed, false otherwise
bool Player::removeTile(int number, Color color) {
    Node* prev = nullptr;
    Node* curr = handHead;
    
    while (curr != nullptr) {
        if (curr->tile->number == number && curr->tile->color == color) {
            if (prev == nullptr) {
                // Removing from head
                handHead = curr->next;
            } else {
                // Bypass the current node
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
