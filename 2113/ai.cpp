#include "ai.h"
#include "validator.h"
#include <algorithm>
#include <vector>
#include <iostream>

// desc: initializes an AIPlayer object with a specified name and difficulty level
// input: name (string) representing the player's name, difficultyLevel (int) for the AI strategy
// output: none
AIPlayer::AIPlayer(std::string name, int difficultyLevel) 
    : Player(name), difficultyLevel(difficultyLevel) {
}

// desc: executes the AI's turn, playing a valid meld to the board based on difficulty level, or drawing a tile if no melds are possible
// input: board (reference to the game Board), deck (reference to the game Deck)
// output: none (modifies game state directly)
void AIPlayer::playTurn(Board& board, Deck& deck) {
    
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
    
  
    bool iceStatus = isIceBroken();

    if (difficultyLevel == 1) {
       
       
        for (int n = 1; n <= 13; n++) {
            std::vector<Tile> potentialMeld;
            bool colorUsed[4] = {false, false, false, false};

            for (const Tile& t : currentHand) {
                if (t.number == n && !colorUsed[t.color]) {
                    colorUsed[t.color] = true;
                    potentialMeld.push_back(t);
                }
            }

            if (potentialMeld.size() >= 3) {
               
                std::vector<Tile> meld = {potentialMeld[0], potentialMeld[1], potentialMeld[2]};
                
                if (validator.isValid(meld)) {
                    int score = validator.sumScore(meld);
                   
                    if (iceStatus || score >= 30) {
                        board.addMeld(meld);
                        for (const Tile& t : meld) {
                            removeTile(t.number, t.color);
                        }
                        setIce(true);
                        std::cout << getName() << " played a valid Group meld!" << std::endl;
                        return; 
                    }
                }
                
             
                if (!iceStatus && potentialMeld.size() == 4) {
                    if (validator.isValid(potentialMeld)) {
                        int score = validator.sumScore(potentialMeld);
                        if (score >= 30) {
                            board.addMeld(potentialMeld);
                            for (const Tile& t : potentialMeld) {
                                removeTile(t.number, t.color);
                            }
                            setIce(true);
                            std::cout << getName() << " played a valid 4-tile Group meld to break ice!" << std::endl;
                            return; 
                        }
                    }
                }
            }
        }

       
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

            for (size_t start = 0; start < colorTiles.size(); start++) {
                std::vector<Tile> run;
                int currentNum = colorTiles[start].number;
                run.push_back(colorTiles[start]);

                for (size_t end = start + 1; end < colorTiles.size(); end++) {
                    int nextNum = colorTiles[end].number;
                    if (nextNum == currentNum + 1) {
                        run.push_back(colorTiles[end]);
                        currentNum = nextNum;

                        if (run.size() >= 3) {
                            if (validator.isValid(run)) {
                                int score = validator.sumScore(run);
                               
                                if (iceStatus || score >= 30) {
                                    board.addMeld(run);
                                    for (const Tile& t : run) {
                                        removeTile(t.number, t.color);
                                    }
                                    setIce(true);
                                    std::cout << getName() << " played a valid Run meld!" << std::endl;
                                    return; 
                                }
                            }
                        }
                    } else if (nextNum > currentNum + 1) {
                        break; 
                    }
                }
            }
        }

      
        if (!deck.isEmpty()) {
            Tile* drawnTile = deck.draw();
            addTile(drawnTile);
            std::cout << getName() << " drew a tile." << std::endl;
        } else {
            std::cout << getName() << " has no valid meld to play, draw pool is empty." << std::endl;
        }
    } 
    
    else if (difficultyLevel == 2) {
        std::vector<std::vector<Tile>> possibleMelds;

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

        int bestScore = -1;
        int bestIdx = -1;

        for (size_t i = 0; i < possibleMelds.size(); i++) {
            int score = validator.sumScore(possibleMelds[i]);
            
            
            if (!iceStatus && score < 30) continue;

            if (score > bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }

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

        if (!deck.isEmpty()) {
            Tile* drawnTile = deck.draw();
            addTile(drawnTile);
            std::cout << getName() << " drew a tile." << std::endl;
        } else {
            std::cout << getName() << " has no valid meld to play, draw pool is empty." << std::endl;
        }
    }
}
