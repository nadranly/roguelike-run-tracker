#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <iostream>
#include <limits>
#include <string>

namespace InputHelper {
    inline int readIntInRange(int minValue, int maxValue) {
        int value;
        while (true) {
            std::cout << "> ";
            if (std::cin >> value && value >= minValue && value <= maxValue) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }

            std::cout << "Invalid input. Enter a number from "
                      << minValue << " to " << maxValue << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    inline std::string readNonEmptyLine(const std::string& prompt) {
        std::string value;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, value);
            if (!value.empty()) {
                return value;
            }
            std::cout << "Input cannot be empty.\n";
        }
    }
}

#endif
