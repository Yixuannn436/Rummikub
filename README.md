# Rummikub

## Team members
- [Hu Yue](https://github.com/HeiHu48983) (UID: 3036221313)
- [Tan Jingwen](https://github.com/Cindy123t) (UID: 3036289975)
- [Wu Yanchen](https://github.com/h3658918) (UID: 3036589181)
- [Zhang Yixuan](https://github.com/Yixuannn436) (UID: 3036480141)
- [Zheng Jiesi](https://github.com/Shirasagi666) (UID: 3036483856)

## Game description

### Objective
Text-Based Rummikub is a terminal-based tile game adapted from the original classic Rummikub board game. Designed for 1-3 human players and 1 AI opponent, the ultimate goal is to be the first player to empty all tiles from their hand.

### Core rules
- Deck: The game consists of 104 tiles (numbers 1-13 in 4 different colors: Red, Blue, Yellow, Black).
- Setup: Each player starts with 14 tiles. The remaining tiles form the draw pool.
- Turn Actions: On their turn, a player must choose to do **ONLY ONE** of the following:
  - Play Tiles: Place one or more valid combinations (Melds) from their hand onto the board.
  - Draw a Tile: Draw one tile from the pool.
- Valid Combinations (Melds):
  - Group: 3 or 4 tiles of the same number but different colors (e.g. Red 7, Blue 7, Black 7).
  - Run: 3 or more consecutive numbers of the same color (e.g. Red 3, Red 4, Red 5).
- Special conditions & simplifications:
  - Initial Play ("Breaking the Ice"): Every single player must successfully "break the ice" before they can play freely. For a player's very first play, the total value of the tiles they put on the board must sum up to 30 points or more. Once this condition is met, they can play any valid melds in subsequent turns without point restrictions.
  - Board Modification: To fit the project scope and maintain smooth gameplay in the terminal, players can only add new melds to the board. They cannot rearrange or split existing melds.
  - Winning & Endgame Conditions:
    - Sudden-Death: There is no complex point accumulation across multiple rounds. The first player to completely empty their hand immediately wins the game.
    - Empty Pool (Stalemate): If the draw pool runs out of tiles and no player can make a valid play, the game ends. All players then count the total face value of their remaining tiles; the player with the lowest total value is declared the winner.

## Features

### Features implemented
- Game setup and tile distribution: Initializes the standard 104-tile deck and automatically distributes 14 starting tiles to 1-3 human players and 1 AI opponent.
- Turn-based action system: Allows players to choose between playing valid combinations (melds) from their hand onto the board or drawing a tile from the pool.
- "Breaking the ice" logic: Implements a point-calculation system that enforces the 30-point minimum threshold for a player's initial move before they can play freely.
- Meld validation and board management: Evaluates played tiles to ensure they form valid Groups (3-4 tiles of the same number, different colors) or Runs (3+ consecutive tiles of the same color).
- AI opponent: Features an automated player capable of scanning its hand to find valid melds or drawing tile from the pool when no moves are available.
- Win conditions: Detects sudden-death victories when a player empties their hand, and calculates the lowest remaining face value to determine a winner in the event of a stalemate (empty draw pool).
- Game save system: Permits players to save their current game progress and load it at a later time to resume play.

### How the coding requirements support these features
- Generation of random events
  - Supports the Game setup and tile distribution feature by randomly shuffling the 104 tiles in the draw pool and distributing them.
  - Be used to introduce unpredictability into the AI opponent's decision-making process when multiple valid moves exist.
- Data structures for storing data
  - struct Tile & class Player: Encapsulates the core properties of a single tile (number, color) and a player's state (score, "ice-breaking" status). This supports Game setup and tile distribution.
  - Custom linked list: Implemented to manage the dynamic size of players' hands. This supports the Turn-based action system, allowing efficient node insertion when drawing tiles and node deletion when playing valid melds.
  - std::vector<Tile> & std::vector<vector<Tile>>: Utilized to store the draw pool and the active board respectively. This ensures efficient Meld validation and board management, handling the continuously growing number of tiles played by all players.
- Dynamic memory management
  - Memory allocation for gameplay (new): Supports the Turn-based action system and board management. We dynamically allocate memory on the heap (e.g. using new Node or new Tile) whenever a player draws a tile or places a new valid meld onto the board.
  - Memory deallocation to prevent leaks (delete): Essential for maintaining performance. When a player plays a tile from their hand, its original memory in the linked list is safely freed.
  - Endgame cleanup: Supports the Winning conditions. Once the game concludes via Sudden-Death or Stalemate, all dynamically allocated objects (remaining pool, active hands, board melds) are systematically destroyed (delete) to ensure zero memory leaks.
- File input/output
  - Powers the Game save system by writing the active game state to a file (such as .txt or .dat).
  - File streams (ifstream and ofstream) are used to record and retrieve the current draw pool, board melds, player hands, and turn order so a session can be paused and accurately reconstructed later.
- Program codes in multiple files
  - Supports all features by modularizing the project into distinct, manageable components. Instead of a single massive file, the game logic is separated into specific .cpp and .h files based on their functionality.


