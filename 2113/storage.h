#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include "tile.h"
#include "player.h"
#include "board.h"
#include "deck.h"

// 负责存档与读档的类
class Storage {
public:
    /**
     * @brief 保存当前游戏状态到文件
     * @param filename 存档文件名
     * @param players 玩家指针列表
     * @param deck 剩余牌堆
     * @param board 桌面上的牌组
     * @param currentTurn 当前轮到的玩家索引
     */
    static void saveGame(const std::string& filename, const std::vector<Player*>& players, 
                        const Deck& deck, const Board& board, int currentTurn);

    /**
     * @brief 从文件读取并恢复游戏状态
     * @return 如果读取成功返回 true
     */
    static bool loadGame(const std::string& filename, std::vector<Player*>& players, 
                        Deck& deck, Board& board, int& currentTurn);
};

#endif