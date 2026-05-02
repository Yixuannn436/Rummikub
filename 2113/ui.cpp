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

        // --- Robustness: Handling invalid input ---
        if (std::cin.fail() || input < min || input > max) {
            std::cout << "Invalid input! Please try again." << std::endl;
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        } else {
            return input;
        }
    }
}

void UI::displayTile(const Tile& t) {
    // Use ANSI color codes
    std::string colorCode;
    switch (t.color) {
        case RED:    colorCode = "\033[31m"; break;
        case BLUE:   colorCode = "\033[34m"; break;
        case YELLOW: colorCode = "\033[33m"; break;
        case BLACK:  colorCode = "\033[37m"; break; // White represents black tiles on dark backgrounds
    }
    
    std::cout << colorCode << "[" << t.number << "]" << "\033[0m ";
}

void UI::clearScreen() {
    // Clear screen for Linux/Unix
    std::cout << "\033[2J\033[1;1H";
}
