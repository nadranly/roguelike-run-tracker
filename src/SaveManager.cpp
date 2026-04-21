#include "SaveManager.h"
#include "Assassin.h"
#include "GameException.h"
#include "Mage.h"
#include "Tank.h"
#include <fstream>
#include <sstream>

void SaveManager::saveCharacters(const std::vector<std::unique_ptr<Character>>& characters,
                                 const std::string& fileName) {
    std::ofstream outFile(fileName);
    if (!outFile) {
        throw GameException("Could not open save file for writing: " + fileName);
    }

    for (const auto& character : characters) {
        outFile << character->getClassName() << '|'
                << character->getName() << '|'
                << character->getHealth() << '|'
                << character->getMaxHealth() << '|'
                << character->getBaseDamage() << '|'
                << character->getWins() << '|'
                << character->getDeaths() << '|'
                << character->getRunsPlayed() << '|'
                << character->getPotions() << '\n';
    }
}

std::vector<std::unique_ptr<Character>> SaveManager::loadCharacters(const std::string& fileName) {
    std::ifstream inFile(fileName);
    if (!inFile) {
        throw GameException("Save file not found. Create and save a character first.");
    }

    std::vector<std::unique_ptr<Character>> characters;
    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string className;
        std::string name;
        std::string healthStr;
        std::string maxHealthStr;
        std::string baseDamageStr;
        std::string winsStr;
        std::string deathsStr;
        std::string runsStr;
        std::string potionsStr;

        if (!std::getline(ss, className, '|') ||
            !std::getline(ss, name, '|') ||
            !std::getline(ss, healthStr, '|') ||
            !std::getline(ss, maxHealthStr, '|') ||
            !std::getline(ss, baseDamageStr, '|') ||
            !std::getline(ss, winsStr, '|') ||
            !std::getline(ss, deathsStr, '|') ||
            !std::getline(ss, runsStr, '|') ||
            !std::getline(ss, potionsStr, '|')) {
            throw GameException("Save file is corrupted or formatted incorrectly.");
        }

        std::unique_ptr<Character> character;

        if (className == "Assassin") {
            character = std::make_unique<Assassin>(name);
        } else if (className == "Tank") {
            character = std::make_unique<Tank>(name);
        } else if (className == "Mage") {
            character = std::make_unique<Mage>(name);
        } else {
            throw GameException("Unknown class found in save file: " + className);
        }

        character->setHealth(std::stoi(healthStr));
        character->setWins(std::stoi(winsStr));
        character->setDeaths(std::stoi(deathsStr));
        character->setRunsPlayed(std::stoi(runsStr));
        character->setPotions(std::stoi(potionsStr));

        characters.push_back(std::move(character));
    }

    return characters;
}
