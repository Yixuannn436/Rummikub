#include "game.h"
#include "ai.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// desc: copy all tiles from a player's linked list hand into a vector
// input: player pointer
// output: a vector containing all tiles in that player's hand
std::vector<Tile> getHandTiles(Player* player) {
    std::vector<Tile> tiles;
    Node* current = player->getHand();

    while (current != nullptr) {
        if (current->tile != nullptr) {
            tiles.push_back(*(current->tile));
        }
        current = current->next;
    }

    return tiles;
}

// desc: count how many tiles a player currently has in hand
// input: player pointer
// output: number of tiles in hand
int getHandCount(Player* player) {
    int count = 0;
    Node* current = player->getHand();

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

// desc: convert tile color enum into readable text
// input: a color enum value
// output: corresponding color string
std::string colorToString(Color color) {
    if (color == RED) return "red";
    if (color == BLUE) return "blue";
    if (color == YELLOW) return "yellow";
    return "black";
}

// desc: print all tiles in one player's hand
// input: player pointer
// output: none
void printHand(Player* player) {
    Node* current = player->getHand();

    if (current == nullptr) {
        std::cout << "(empty)" << std::endl;
        return;
    }

    int index = 1;
    while (current != nullptr) {
        std::cout << index << ". ";
        if (current->tile != nullptr) {
            UI::displayTile(*(current->tile));
            std::cout << " (" << colorToString(current->tile->color) << " " 
                      << current->tile->number << ")";
        }
        std::cout << std::endl;
        current = current->next;
        index++;
    }
}

// desc: print all melds currently on the board
// input: board reference
// output: none
void printBoard(Board& board) {
    std::vector<std::vector<Tile>> table = board.getTable();

    if (table.empty()) {
        std::cout << "(board is empty)" << std::endl;
        return;
    }

    for (size_t i = 0; i < table.size(); i++) {
        std::cout << "meld " << i + 1 << ": ";
        for (const Tile& tile : table[i]) {
            UI::displayTile(tile);
        }
        std::cout << std::endl;
    }
}

// desc: check whether the player's hand contains all tiles in a given meld
// input: player pointer and a meld vector
// output: true if the player has all those tiles, false otherwise
bool handContainsMeld(Player* player, const std::vector<Tile>& meld) {
    std::vector<Tile> handTiles = getHandTiles(player);
    std::vector<bool> used(handTiles.size(), false);

    for (const Tile& needed : meld) {
        bool found = false;

        for (size_t i = 0; i < handTiles.size(); i++) {
            if (!used[i] &&
                handTiles[i].number == needed.number &&
                handTiles[i].color == needed.color) {
                used[i] = true;
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

// desc: check whether a player still has any possible valid play
// input: player pointer
// output: true if the player can still play at least one valid meld
bool canPlayerPlay(Player* player) {
    std::vector<Tile> handTiles = getHandTiles(player);
    Validator validator;

    if (handTiles.size() < 3) {
        return false;
    }

    bool needThirty = !player->isIceBroken();

    for (int n = 1; n <= 13; n++) {
        std::vector<Tile> group;
        bool usedColor[4] = {false, false, false, false};

        for (const Tile& tile : handTiles) {
            if (tile.number == n && !usedColor[tile.color]) {
                usedColor[tile.color] = true;
                group.push_back(tile);
            }
        }

        if (group.size() >= 3) {
            std::vector<Tile> meld3 = {group[0], group[1], group[2]};
            if (validator.isValid(meld3)) {
                if (!needThirty || validator.sumScore(meld3) >= 30) {
                    return true;
                }
            }
        }

        if (group.size() == 4) {
            if (validator.isValid(group)) {
                if (!needThirty || validator.sumScore(group) >= 30) {
                    return true;
                }
            }
        }
    }

    Color colors[4] = {RED, BLUE, YELLOW, BLACK};

    for (Color color : colors) {
        std::vector<Tile> sameColor;

        for (const Tile& tile : handTiles) {
            if (tile.color == color) {
                sameColor.push_back(tile);
            }
        }

        std::sort(sameColor.begin(), sameColor.end(),
            [](const Tile& a, const Tile& b) {
                return a.number < b.number;
            });

        std::vector<Tile> uniqueTiles;
        for (const Tile& tile : sameColor) {
            if (uniqueTiles.empty() || uniqueTiles.back().number != tile.number) {
                uniqueTiles.push_back(tile);
            }
        }

        for (size_t i = 0; i < uniqueTiles.size(); i++) {
            std::vector<Tile> run;
            run.push_back(uniqueTiles[i]);
            int currentNumber = uniqueTiles[i].number;

            for (size_t j = i + 1; j < uniqueTiles.size(); j++) {
                if (uniqueTiles[j].number == currentNumber + 1) {
                    run.push_back(uniqueTiles[j]);
                    currentNumber = uniqueTiles[j].number;

                    if (run.size() >= 3 && validator.isValid(run)) {
                        if (!needThirty || validator.sumScore(run) >= 30) {
                            return true;
                        }
                    }
                } else if (uniqueTiles[j].number > currentNumber + 1) {
                    break;
                }
            }
        }
    }

    return false;
}

// desc: initialize game status values
// input: none
// output: none
Game::Game() : turnIndex(0), isOver(false) {
}

// desc: free all dynamically allocated player objects
// input: none
// output: none
Game::~Game() {
    for (Player* player : players) {
        delete player;
    }
    players.clear();
}

// desc: show the main menu and start a new game, load a game, or quit
// input: none
// output: none
void Game::startMenu() {
    UI::printWelcome();
    std::cout << "1. new game" << std::endl;
    std::cout << "2. load game" << std::endl;
    std::cout << "3. quit" << std::endl;

    int choice = UI::getValidInt(1, 3);

    if (choice == 1) {
        setup();
        playLoop();
    } else if (choice == 2) {
        std::cout << "enter save file name: ";
        std::string filename;
        std::cin >> filename;

        if (Storage::loadGame(filename, players, deck, board, turnIndex)) {
            std::cout << "game loaded successfully." << std::endl;
            playLoop();
        } else {
            std::cout << "failed to load game file." << std::endl;
        }
    } else {
        std::cout << "goodbye!" << std::endl;
    }
}

// desc: create players, choose ai difficulty, and deal 14 tiles to each player
// input: none
// output: none
void Game::setup() {
    for (Player* player : players) {
        delete player;
    }
    players.clear();

    board.reset();
    turnIndex = 0;
    isOver = false;

    std::cout << "number of human players (1-3):" << std::endl;
    int humanCount = UI::getValidInt(1, 3);

    std::cout << "ai difficulty (1 easy, 2 hard):" << std::endl;
    int difficulty = UI::getValidInt(1, 2);

    for (int i = 0; i < humanCount; i++) {
        std::cout << "enter player " << i + 1 << " name: ";
        std::string name;
        std::cin >> name;
        players.push_back(new Player(name));
    }

    players.push_back(new AIPlayer("computer", difficulty));

    for (int round = 0; round < 14; round++) {
        for (Player* player : players) {
            Tile* tile = deck.draw();
            if (tile != nullptr) {
                player->addTile(tile);
            }
        }
    }

    std::cout << "game setup complete." << std::endl;
}

// desc: run the main game loop until a win condition is reached
// input: none
// output: none
void Game::playLoop() {
    while (!isOver) {
        if (players.empty()) {
            isOver = true;
            break;
        }

        Player* currentPlayer = players[turnIndex];
        showState(currentPlayer);

        AIPlayer* aiPlayer = dynamic_cast<AIPlayer*>(currentPlayer);
        if (aiPlayer != nullptr) {
            std::cout << currentPlayer->getName() << "'s turn (ai)." << std::endl;
            aiPlayer->playTurn(board, deck);
        } else {
            doTurn(currentPlayer);
        }

        if (checkWin()) {
            break;
        }

        nextPlayer();
    }
}

// desc: process one human player's turn
// input: player pointer
// output: none
void Game::doTurn(Player* player) {
    std::cout << std::endl;
    std::cout << player->getName() << "'s turn" << std::endl;
    std::cout << "1. play one meld" << std::endl;
    std::cout << "2. draw one tile" << std::endl;
    std::cout << "3. save and quit" << std::endl;

    int choice = UI::getValidInt(1, 3);

    if (choice == 1) {
        int handCount = getHandCount(player);

        if (handCount < 3) {
            std::cout << "you do not have enough tiles to form a meld." << std::endl;
            return;
        }

        std::cout << "how many tiles do you want to play in this meld?" << std::endl;
        int meldSize = UI::getValidInt(3, handCount);

        std::vector<Tile> meld;
        for (int i = 0; i < meldSize; i++) {
            std::cout << "tile " << i + 1 << " number (1-13):" << std::endl;
            int number = UI::getValidInt(1, 13);

            std::cout << "tile " << i + 1 << " color (0 red, 1 blue, 2 yellow, 3 black):" << std::endl;
            int colorValue = UI::getValidInt(0, 3);

            Tile tile;
            tile.number = number;
            tile.color = static_cast<Color>(colorValue);
            meld.push_back(tile);
        }

        if (!handContainsMeld(player, meld)) {
            std::cout << "you do not have those exact tiles in hand." << std::endl;
            return;
        }

        if (!validator.isValid(meld)) {
            std::cout << "invalid meld." << std::endl;
            return;
        }

        int score = validator.sumScore(meld);
        if (!player->isIceBroken() && score < 30) {
            std::cout << "first successful play must be at least 30 points." << std::endl;
            return;
        }

        for (const Tile& tile : meld) {
            player->removeTile(tile.number, tile.color);
        }

        board.addMeld(meld);

        if (!player->isIceBroken()) {
            player->setIce(true);
        }

        std::cout << "meld played successfully." << std::endl;
    } 
    else if (choice == 2) {
        if (deck.isEmpty()) {
            std::cout << "draw pool is empty." << std::endl;
        } else {
            Tile* drawnTile = deck.draw();
            player->addTile(drawnTile);
            std::cout << "you drew ";
            UI::displayTile(*drawnTile);
            std::cout << std::endl;
        }
    } 
    else {
        saveAndQuit();
    }
}

// desc: clear the screen and show current board state and player hand
// input: player pointer
// output: none
void Game::showState(Player* player) {
    UI::clearScreen();

    std::cout << "============================" << std::endl;
    std::cout << "current player: " << player->getName() << std::endl;
    std::cout << "tiles left in pool: " << deck.getSize() << std::endl;
    std::cout << "ice broken: " << (player->isIceBroken() ? "yes" : "no") << std::endl;
    std::cout << "============================" << std::endl;

    std::cout << std::endl;
    std::cout << "board:" << std::endl;
    printBoard(board);

    std::cout << std::endl;
    std::cout << "your hand:" << std::endl;
    printHand(player);

    std::cout << std::endl;
}

// desc: move the turn index to the next player
// input: none
// output: none
void Game::nextPlayer() {
    if (!players.empty()) {
        turnIndex = (turnIndex + 1) % players.size();
    }
}

// desc: check whether the game has ended by empty hand or stalemate
// input: none
// output: true if the game is over, false otherwise
bool Game::checkWin() {
    for (Player* player : players) {
        if (player->getHand() == nullptr) {
            std::cout << player->getName() << " wins by emptying all tiles." << std::endl;
            isOver = true;
            return true;
        }
    }

    if (deck.isEmpty()) {
        bool anyoneCanStillPlay = false;

        for (Player* player : players) {
            if (canPlayerPlay(player)) {
                anyoneCanStillPlay = true;
                break;
            }
        }

        if (!anyoneCanStillPlay) {
            int bestScore = -1;
            Player* winner = nullptr;

            for (Player* player : players) {
                int score = player->getHandValue();
                std::cout << player->getName() << " remaining score: " << score << std::endl;

                if (winner == nullptr || score < bestScore) {
                    bestScore = score;
                    winner = player;
                }
            }

            if (winner != nullptr) {
                std::cout << winner->getName() << " wins by lowest remaining score." << std::endl;
            }

            isOver = true;
            return true;
        }
    }

    return false;
}

// desc: save the current game state and end the game loop
// input: none
// output: none
void Game::saveAndQuit() {
    std::cout << "enter save file name: ";
    std::string filename;
    std::cin >> filename;

    Storage::saveGame(filename, players, deck, board, turnIndex);
    std::cout << "game saved." << std::endl;
    isOver = true;
}