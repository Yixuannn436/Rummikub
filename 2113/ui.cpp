#include "ui.h"
#include <iostream>
#include <limits>

void UI::printWelcome() {
    std::cout << "========================================" << std::endl;
    std::cout << "    WELCOME TO SIMPLIFIED RUMMIKUB!     " << std::endl;
    std::cout << "========================================" << std::endl;
}

int UI::getValidInt(int min, int max) {
    int input;
    while (true) {
        std::cout << "Please enter a number (" << min << "-" << max << "): ";
        std::cin >> input;

        // --- 核心考点：Robustness (处理非法输入) ---
        if (std::cin.fail() || input < min || input > max) {
            std::cout << "Invalid input! Please try again." << std::endl;
            std::cin.clear(); // 清除错误标记
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区
        } else {
            return input;
        }
    }
}

void UI::displayTile(const Tile& t) {
    // 使用 ANSI 颜色代码
    std::string colorCode;
    switch (t.color) {
        case RED:    colorCode = "\033[31m"; break;
        case BLUE:   colorCode = "\033[34m"; break;
        case YELLOW: colorCode = "\033[33m"; break;
        case BLACK:  colorCode = "\033[37m"; break; // 白色代表黑色背景下的黑牌
    }
    
    std::cout << colorCode << "[" << t.number << "]" << "\033[0m ";
}

void UI::clearScreen() {
    // Linux 下清屏
    std::cout << "\033[2J\033[1;1H";
}