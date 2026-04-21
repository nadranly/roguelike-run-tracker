#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <vector>
#include "Character.h"

class Game {
private:
    std::vector<std::unique_ptr<Character>> roster;
    int activeIndex;
    std::string saveFile;

    void displayWelcome() const;
    void displayMainMenu() const;
    void createCharacter();
    void chooseActiveCharacter();
    void viewRoster() const;
    void startRun();
    void saveGame() const;
    void loadGame();
    void removeCharacter();
    Character* getActiveCharacter();
    void printCharacterCard(const Character& character, bool showIndex = false, int index = 0) const;

public:
    explicit Game(const std::string& saveFile = "data/save_data.txt");

    void run();
};

#endif
