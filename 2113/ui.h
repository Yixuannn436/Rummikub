#ifndef UI_H
#define UI_H

#include <string>
#include "tile.h"

class UI {
public:
    static void printWelcome();
    
    /**
     * @brief 获取合法的整数输入，带异常处理
     */
    static int getValidInt(int min, int max);

    /**
     * @brief 带颜色打印一张牌
     */
    static void displayTile(const Tile& t);

    static void clearScreen();
};

#endif