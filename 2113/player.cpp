#include "player.h"
#include <iostream>

Player::Player(std::string playerName) 
    : name(playerName), handHead(nullptr), iceBroken(false) {}

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

void Player::addTile(Tile* tile) {
    Node* newNode = new Node;
    newNode->tile = tile;
    newNode->next = handHead;
    handHead = newNode;
}

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

int Player::getHandValue() {
    int total = 0;
    Node* current = handHead;
    while (current != nullptr) {
        total += current->tile->number;
        current = current->next;
    }
    return total;
}

bool Player::isIceBroken() {
    return iceBroken;
}

void Player::setIce(bool status) {
    iceBroken = status;
}

Node* Player::getHand() {
    return handHead;
}

std::string Player::getName() {
    return name;
}
