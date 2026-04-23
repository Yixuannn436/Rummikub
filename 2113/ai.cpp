#include "ai.h"
#include "validator.h"
#include "deck.h"
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

// Simple mode --ignore ice-breaking
void AIController::playTurnEasy(Player& aiPlayer, Board& board, Deck& deck) {
    bool hasPlayed = false;
    const std::string colors[] = {"Red", "Blue", "Yellow", "Black"};

    
    for (int n = 1; n <= 13; n++) {
        std::vector<int> indices;
        for (int i = 0; i < aiPlayer.getHandSize(); i++) {
            if (aiPlayer.getTileAt(i)->number == n) {
                indices.push_back(i);
            }
        }
        if (indices.size() >= 3) {
            std::vector<Tile*> meld;
            for (int i = 0; i < 3; i++) {
                meld.push_back(aiPlayer.getTileAt(indices[i]));
            }
           
            std::sort(indices.begin(), indices.end(), std::greater<int>());
            for (int i = 0; i < 3; i++) {
                aiPlayer.removeTileFromHand(indices[i]);
            }
            board.addMeldToBoard(meld);
            hasPlayed = true;
            std::cout << "AI played a meld!" << std::endl;
            return;
        }
    }

   
    if (!hasPlayed) {
        for (const std::string& c : colors) {
            std::vector<int> indices;
            for (int i = 0; i < aiPlayer.getHandSize(); i++) {
                if (aiPlayer.getTileAt(i)->color == c) {
                    indices.push_back(i);
                }
            }
            if (indices.size() >= 3) {
                std::vector<Tile*> meld;
                for (int i = 0; i < 3; i++) {
                    meld.push_back(aiPlayer.getTileAt(indices[i]));
                }
                std::sort(indices.begin(), indices.end(), std::greater<int>());
                for (int i = 0; i < 3; i++) {
                    aiPlayer.removeTileFromHand(indices[i]);
                }
                board.addMeldToBoard(meld);
                hasPlayed = true;
                std::cout << "AI played a meld!" << std::endl;
                return;
            }
        }
    }

    
    if (!hasPlayed && !deck.isEmpty()) {
        Tile* drawnTile = deck.drawTile();
        aiPlayer.addTileToHand(drawnTile);
        std::cout << "AI drew a tile." << std::endl;
    }
}

// Hard Mode -- ice-breaking
void AIController::playTurnHard(Player& aiPlayer, Board& board, Deck& deck) {
    std::vector<std::pair<std::vector<Tile*>, std::vector<int>>> possibleMelds;
    const std::string colors[] = {"Red", "Blue", "Yellow", "Black"};

    
    for (int n = 1; n <= 13; n++) {
        std::vector<int> indices;
        bool seenColors[4] = {false, false, false, false};
        for (int i = 0; i < aiPlayer.getHandSize(); i++) {
            Tile* t = aiPlayer.getTileAt(i);
            if (t->number == n) {
                int cIdx = (t->color == "Red" ? 0 : (t->color == "Blue" ? 1 : (t->color == "Yellow" ? 2 : 3)));
                if (!seenColors[cIdx]) {
                    seenColors[cIdx] = true;
                    indices.push_back(i);
                }
            }
        }
        if (indices.size() >= 3) {
            std::vector<Tile*> m3 = {aiPlayer.getTileAt(indices[0]), aiPlayer.getTileAt(indices[1]), aiPlayer.getTileAt(indices[2])};
            std::vector<int> id3 = {indices[0], indices[1], indices[2]};
            possibleMelds.emplace_back(m3, id3);
            if (indices.size() == 4) {
                std::vector<Tile*> m4 = m3;
                m4.push_back(aiPlayer.getTileAt(indices[3]));
                possibleMelds.emplace_back(m4, indices);
            }
        }
    }

   
    for (const std::string& c : colors) {
        std::vector<int> colorIndices;
        for (int i = 0; i < aiPlayer.getHandSize(); i++) {
            if (aiPlayer.getTileAt(i)->color == c) {
                colorIndices.push_back(i);
            }
        }
      
        for (size_t i = 0; i < colorIndices.size(); i++) {
            for (size_t j = i + 1; j < colorIndices.size(); j++) {
                if (aiPlayer.getTileAt(colorIndices[i])->number > aiPlayer.getTileAt(colorIndices[j])->number) {
                    std::swap(colorIndices[i], colorIndices[j]);
                }
            }
        }
       
        for (size_t i = 0; i < colorIndices.size(); i++) {
            std::vector<Tile*> run;
            std::vector<int> runIds;
            run.push_back(aiPlayer.getTileAt(colorIndices[i]));
            runIds.push_back(colorIndices[i]);
            int currentNum = run.back()->number;

            for (size_t j = i + 1; j < colorIndices.size(); j++) {
                Tile* nextTile = aiPlayer.getTileAt(colorIndices[j]);
                if (nextTile->number == currentNum + 1) {
                    run.push_back(nextTile);
                    runIds.push_back(colorIndices[j]);
                    currentNum++;
                    if (run.size() >= 3) {
                        possibleMelds.emplace_back(run, runIds);
                    }
                } else if (nextTile->number > currentNum + 1) {
                    break;
                }
            }
        }
    }

   
    int bestScore = -1;
    int bestIdx = -1;
    bool& iceBroken = aiPlayer.has_broken_ice;

    for (size_t i = 0; i < possibleMelds.size(); i++) {
        int score = Validator::calculateScore(possibleMelds[i].first);
        if (!iceBroken && score < 30) continue; 
        if (score > bestScore) {
            bestScore = score;
            bestIdx = i;
        }
    }

   
    if (bestIdx != -1) {
        auto& bestMeld = possibleMelds[bestIdx];
        std::vector<int> indicesToRemove = bestMeld.second;
        std::sort(indicesToRemove.begin(), indicesToRemove.end(), std::greater<int>());
        for (int idx : indicesToRemove) {
            aiPlayer.removeTileFromHand(idx);
        }
        board.addMeldToBoard(bestMeld.first);
        iceBroken = true;
        std::cout << "AI played a meld!" << std::endl;
        return;
    }

   
    if (!deck.isEmpty()) {
        Tile* drawnTile = deck.drawTile();
        aiPlayer.addTileToHand(drawnTile);
        std::cout << "AI drew a tile." << std::endl;
    }
}
