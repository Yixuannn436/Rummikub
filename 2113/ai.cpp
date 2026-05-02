#include "ai.h"
#include "validator.h"
#include <algorithm>
#include <vector>
#include <iostream>

// Constructor for AIPlayer
AIPlayer::AIPlayer(std::string name, int difficultyLevel)
    : Player(name), difficultyLevel(difficultyLevel) {
}

// Main logic for the AI's turn
void AIPlayer::playTurn(Board& board, Deck& deck) {

    // Convert the linked list hand into a vector for easier manipulation
    std::vector<Tile> currentHand;
    Node* current = getHand();
    while (current != nullptr) {
        if (current->tile != nullptr) {
            currentHand.push_back(*(current->tile));
        }
        current = current->next;
    }

    Validator validator;
    bool hasPlayed = false;

    // DIFFICULTY LEVEL 1: Simple strategy (plays the first valid meld found)
    if (difficultyLevel == 1) {
        
        // Try to find a Group (same number, different colors)
        for (int n = 1; n <= 13; n++) {
            std::vector<Tile> potentialMeld;
            bool colorUsed[4] = {false, false, false, false};

            for (const Tile& t : currentHand) {
                if (t.number == n && !colorUsed[t.color]) {
                    colorUsed[t.color] = true;
                    potentialMeld.push_back(t);
                }
            }

            // If a group of 3 or more is found, play it immediately
            if (potentialMeld.size() >= 3) {
                std::vector<Tile> meld = {potentialMeld[0], potentialMeld[1], potentialMeld[2]};

                if (validator.isValid(meld)) {
                    board.addMeld(meld);
                    // Remove tiles from AI's hand
                    for (const Tile& t : meld) {
                        removeTile(t.number, t.color);
                    }
                    setIce(true);
                    std::cout << getName() << " played a valid Group meld!" << std::endl;
                    return;
                }
            }
        }

        // Try to find a Run (consecutive numbers, same color)
        Color colors[] = {RED, BLUE, YELLOW, BLACK};
        for (Color c : colors) {
            std::vector<Tile> colorTiles;
            for (const Tile& t : currentHand) {
                if (t.color == c) {
                    colorTiles.push_back(t);
                }
            }

            // Sort tiles by number to find sequences
            std::sort(colorTiles.begin(), colorTiles.end(), [](const Tile& a, const Tile& b) {
                return a.number < b.number;
            });

            for (size_t start = 0; start < colorTiles.size(); start++) {
                std::vector<Tile> run;
                int currentNum = colorTiles[start].number;
                run.push_back(colorTiles[start]);

                for (size_t end = start + 1; end < colorTiles.size(); end++) {
                    int nextNum = colorTiles[end].number;
                    if (nextNum == currentNum + 1) {
                        run.push_back(colorTiles[end]);
                        currentNum = nextNum;

                        // Play the run if it has 3 or more tiles
                        if (run.size() >= 3) {
                            if (validator.isValid(run)) {
                                board.addMeld(run);
                                for (const Tile& t : run) {
                                    removeTile(t.number, t.color);
                                }
                                setIce(true);
                                std::cout << getName() << " played a valid Run meld!" << std::endl;
                                return;
                            }
                        }
                    } else if (nextNum > currentNum + 1) {
                        break; // Sequence broken
                    }
                }
            }
        }

        // If no moves found, draw a tile
        if (!deck.isEmpty()) {
            Tile* drawnTile = deck.draw();
            addTile(drawnTile);
            std::cout << getName() << " drew a tile." << std::endl;
        } else {
            std::cout << getName() << " has no valid meld to play, draw pool is empty." << std::endl;
        }
    }

    // DIFFICULTY LEVEL 2: Smart strategy (finds all options and picks the highest score)
    else if (difficultyLevel == 2) {
        std::vector<std::vector<Tile>> possibleMelds;

        // Search for all possible Groups
        for (int n = 1; n <= 13; n++) {
            std::vector<Tile> groupTiles;
            bool seenColors[4] = {false, false, false, false};

            for (const Tile& t : currentHand) {
                if (t.number == n && !seenColors[t.color]) {
                    seenColors[t.color] = true;
                    groupTiles.push_back(t);
                }
            }

            if (groupTiles.size() >= 3) {
                std::vector<Tile> m3 = {groupTiles[0], groupTiles[1], groupTiles[2]};
                if (validator.isValid(m3)) {
                    possibleMelds.push_back(m3);
                }
                if (groupTiles.size() == 4) {
                    std::vector<Tile> m4 = groupTiles;
                    if (validator.isValid(m4)) {
                        possibleMelds.push_back(m4);
                    }
                }
            }
        }

        // Search for all possible Runs
        Color colors[] = {RED, BLUE, YELLOW, BLACK};
        for (Color c : colors) {
            std::vector<Tile> colorTiles;
            for (const Tile& t : currentHand) {
                if (t.color == c) {
                    colorTiles.push_back(t);
                }
            }

            std::sort(colorTiles.begin(), colorTiles.end(), [](const Tile& a, const Tile& b) {
                return a.number < b.number;
            });

            for (size_t i = 0; i < colorTiles.size(); i++) {
                std::vector<Tile> run;
                run.push_back(colorTiles[i]);
                int currentNum = colorTiles[i].number;

                for (size_t j = i + 1; j < colorTiles.size(); j++) {
                    if (colorTiles[j].number == currentNum + 1) {
                        run.push_back(colorTiles[j]);
                        currentNum++;
                        if (run.size() >= 3) {
                            if (validator.isValid(run)) {
                                possibleMelds.push_back(run);
                            }
                        }
                    } else if (colorTiles[j].number > currentNum + 1) {
                        break;
                    }
                }
            }
        }

        // Find the meld with the highest score
        int bestScore = -1;
        int bestIdx = -1;
        bool iceStatus = isIceBroken();

        for (size_t i = 0; i < possibleMelds.size(); i++) {
            int score = validator.sumScore(possibleMelds[i]);

            // First play must be at least 30 points
            if (!iceStatus && score < 30) continue;

            if (score > bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }

        // If a valid best move exists, play it
        if (bestIdx != -1) {
            std::vector<Tile> bestMeld = possibleMelds[bestIdx];

            for (const Tile& t : bestMeld) {
                removeTile(t.number, t.color);
            }

            board.addMeld(bestMeld);
            setIce(true);
            std::cout << getName() << " played a valid meld! Score: " << bestScore << std::endl;
            return;
        }

        // Fallback: draw a tile
        if (!deck.isEmpty()) {
            Tile* drawnTile = deck.draw();
            addTile(drawnTile);
            std::cout << getName() << " drew a tile." << std::endl;
        } else {
            std::cout << getName() << " has no valid meld to play, draw pool is empty." << std::endl;
        }
    }
}

