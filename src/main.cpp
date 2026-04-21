#include "Game.h"
#include <exception>
#include <iostream>

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& exception) {
        std::cout << "Fatal error: " << exception.what() << '\n';
    }

    return 0;
}
