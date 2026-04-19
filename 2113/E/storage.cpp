#include "storage.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Storage::saveGame(const std::string& filename, const std::vector<Player*>& players, 
                      const Deck& deck, const Board& board, int currentTurn) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for saving." << std::endl;
        return;
    }

    // 1. 保存全局信息：玩家人数、当前轮次
    outFile << players.size() << " " << currentTurn << std::endl;

    // 2. 保存牌堆状态 (Deck)
    outFile << deck.tiles.size() << std::endl;
    for (auto t : deck.tiles) {
        outFile << t->color << " " << t->number << " ";
    }
    outFile << std::endl;

    // 3. 保存每个玩家的手牌
    for (auto p : players) {
        outFile << p->name << " " << p->isAI << " " << p->has_broken_ice << " " << p->hand.size() << std::endl;
        for (auto t : p->hand) {
            outFile << t->color << " " << t->number << " ";
        }
        outFile << std::endl;
    }

    // 4. 保存桌面的牌组 (Board)
    outFile << board.melds.size() << std::endl;
    for (const auto& meld : board.melds) {
        outFile << meld.size() << " ";
        for (auto t : meld) {
            outFile << t->color << " " << t->number << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
    std::cout << "Game saved successfully to " << filename << std::endl;
}

bool Storage::loadGame(const std::string& filename, std::vector<Player*>& players, 
                      Deck& deck, Board& board, int& currentTurn) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return false;

    // --- 关键点：加载前清理旧的动态内存 ---
    for (auto p : players) delete p;
    players.clear();
    for (auto t : deck.tiles) delete t;
    deck.tiles.clear();
    // (Board 的清理逻辑同理...)

    int numPlayers;
    inFile >> numPlayers >> currentTurn;

    // 读取牌堆
    int deckSize;
    inFile >> deckSize;
    for (int i = 0; i < deckSize; ++i) {
        int c, n;
        inFile >> c >> n;
        deck.tiles.push_back(new Tile{n, static_cast<Color>(c)}); // 使用 new 体现动态内存管理
    }

    // 读取玩家
    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        bool isAI, brokenIce;
        int handSize;
        inFile >> name >> isAI >> brokenIce >> handSize;
        Player* p = new Player(name, isAI);
        p->has_broken_ice = brokenIce;
        for (int j = 0; j < handSize; ++j) {
            int c, n;
            inFile >> c >> n;
            p->hand.push_back(new Tile{n, static_cast<Color>(c)});
        }
        players.push_back(p);
    }

    // 读取桌面牌组... (此处省略重复的解析逻辑)
    
    inFile.close();
    return true;
}