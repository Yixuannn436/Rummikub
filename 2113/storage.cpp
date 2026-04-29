#include "storage.h"
#include "ai.h"
#include <fstream>
#include <iostream>

// desc: save game state to a text file
// input: filename, players list, deck, board, current turn
// output: true if file is saved successfully, false otherwise
bool Storage::saveGame(std::string filename, const std::vector<Player*>& players, Deck& deck, Board& board, int currentTurn) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "error: could not open file for saving." << std::endl;
        return false;
    }

    // 1. Save global info
    outFile << players.size() << " " << currentTurn << std::endl;

    // 2. Save deck
    std::vector<Tile*> deckTiles = deck.getTiles();
    outFile << deckTiles.size() << std::endl;
    for (Tile* t : deckTiles) {
        outFile << t->color << " " << t->number << " ";
    }
    outFile << std::endl;

    // 3. Save players
    for (Player* p : players) {
        // Use dynamic_cast to check if player is AI
        bool isAI = (dynamic_cast<AIPlayer*>(p) != nullptr);
        
        int handSize = 0;
        Node* current = p->getHand();
        while (current != nullptr) {
            handSize++;
            current = current->next;
        }
        
        outFile << p->getName() << " " << isAI << " " << p->isIceBroken() << " " << handSize << std::endl;
        
        current = p->getHand();
        while (current != nullptr) {
            outFile << current->tile->color << " " << current->tile->number << " ";
            current = current->next;
        }
        outFile << std::endl;
    }

    // 4. Save board
    std::vector<std::vector<Tile>> melds = board.getTable();
    outFile << melds.size() << std::endl;
    for (const auto& meld : melds) {
        outFile << meld.size() << " ";
        for (const Tile& t : meld) {
            outFile << t.color << " " << t.number << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
    return true;
}

// desc: load game state from a text file
// input: filename, players list, deck, board, current turn reference
// output: true if file is loaded successfully, false otherwise
bool Storage::loadGame(std::string filename, std::vector<Player*>& players, Deck& deck, Board& board, int& currentTurn) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return false;

    // Clear old memory
    for (Player* p : players) {
        delete p;
    }
    players.clear();
    deck.clearDeck();
    board.reset();

    int numPlayers;
    inFile >> numPlayers >> currentTurn;

    // Load deck
    int deckSize;
    inFile >> deckSize;
    for (int i = 0; i < deckSize; ++i) {
        int c, n;
        inFile >> c >> n;
        Tile* t = new Tile;
        t->number = n;
        t->color = static_cast<Color>(c);
        deck.addTileToBottom(t);
    }

    // Load players
    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        bool isAI, brokenIce;
        int handSize;
        inFile >> name >> isAI >> brokenIce >> handSize;
        
        Player* p;
        if (isAI) {
            p = new AIPlayer(name, 1); // Default to easy, logic maintains state
        } else {
            p = new Player(name);
        }
        p->setIce(brokenIce);
        
        for (int j = 0; j < handSize; ++j) {
            int c, n;
            inFile >> c >> n;
            Tile* t = new Tile;
            t->number = n;
            t->color = static_cast<Color>(c);
            p->addTile(t);
        }
        players.push_back(p);
    }

    // Load board
    int numMelds;
    inFile >> numMelds;
    for (int i = 0; i < numMelds; ++i) {
        int meldSize;
        inFile >> meldSize;
        std::vector<Tile> meld;
        for (int j = 0; j < meldSize; ++j) {
            int c, n;
            inFile >> c >> n;
            Tile t;
            t.number = n;
            t.color = static_cast<Color>(c);
            meld.push_back(t);
        }
        board.addMeld(meld);
    }
    
    inFile.close();
    return true;
}
