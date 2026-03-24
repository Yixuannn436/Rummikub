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

