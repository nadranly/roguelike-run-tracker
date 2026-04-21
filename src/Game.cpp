#include "Game.h"
#include "Assassin.h"
#include "GameException.h"
#include "InputHelper.h"
#include "Mage.h"
#include "SaveManager.h"
#include "Tank.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

Game::Game(const std::string& saveFile)
    : activeIndex(-1), saveFile(saveFile) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::displayWelcome() const {
    std::cout << "========================================\n";
    std::cout << "      Roguelike Run Tracker\n";
    std::cout << "========================================\n";
    std::cout << "Create heroes, run dungeons, and save stats.\n\n";
}

void Game::displayMainMenu() const {
    std::cout << "\nMain Menu\n";
    std::cout << "1. Create character\n";
    std::cout << "2. Choose active character\n";
    std::cout << "3. Start dungeon run\n";
    std::cout << "4. View roster\n";
    std::cout << "5. Save roster to file\n";
    std::cout << "6. Load roster from file\n";
    std::cout << "7. Remove character\n";
    std::cout << "8. Exit\n";
}

void Game::printCharacterCard(const Character& character, bool showIndex, int index) const {
    if (showIndex) {
        std::cout << "[" << index + 1 << "] ";
    }

    std::cout << character.getName() << " (" << character.getClassName() << ")";
    if (activeIndex >= 0 && activeIndex < static_cast<int>(roster.size()) &&
        &character == roster[activeIndex].get()) {
        std::cout << "  <ACTIVE>";
    }
    std::cout << '\n';

    std::cout << "  HP: " << character.getHealth() << "/" << character.getMaxHealth()
              << " | Potions: " << character.getPotions()
              << " | Runs: " << character.getRunsPlayed()
              << " | Wins: " << character.getWins()
              << " | Deaths: " << character.getDeaths() << '\n';
}

void Game::createCharacter() {
    std::cout << "\nChoose a class:\n";
    std::cout << "1. Assassin - high burst, lower health\n";
    std::cout << "2. Tank - more health, steady damage\n";
    std::cout << "3. Mage - balanced with strong spell burst\n";

    int classChoice = InputHelper::readIntInRange(1, 3);
    std::string name = InputHelper::readNonEmptyLine("Enter character name: ");

    std::unique_ptr<Character> newCharacter;

    switch (classChoice) {
        case 1:
            newCharacter = std::make_unique<Assassin>(name);
            break;
        case 2:
            newCharacter = std::make_unique<Tank>(name);
            break;
        case 3:
            newCharacter = std::make_unique<Mage>(name);
            break;
        default:
            throw GameException("Invalid class selection.");
    }

    roster.push_back(std::move(newCharacter));
    if (activeIndex == -1) {
        activeIndex = 0;
    }

    std::cout << "Character created successfully.\n";
}

void Game::chooseActiveCharacter() {
    if (roster.empty()) {
        throw GameException("No characters available. Create one first.");
    }

    viewRoster();
    std::cout << "Choose the number of the active character:\n";
    int choice = InputHelper::readIntInRange(1, static_cast<int>(roster.size()));
    activeIndex = choice - 1;
    std::cout << roster[activeIndex]->getName() << " is now active.\n";
}

void Game::viewRoster() const {
    if (roster.empty()) {
        std::cout << "No characters in the roster yet.\n";
        return;
    }

    std::cout << "\n=== Roster ===\n";
    for (size_t i = 0; i < roster.size(); ++i) {
        printCharacterCard(*roster[i], true, static_cast<int>(i));
    }
}

Character* Game::getActiveCharacter() {
    if (activeIndex < 0 || activeIndex >= static_cast<int>(roster.size())) {
        throw GameException("No active character selected.");
    }
    return roster[activeIndex].get();
}

void Game::startRun() {
    Character* hero = getActiveCharacter();
    hero->addRun();

    std::vector<Enemy> enemies = {
        Enemy("Slime", 35 + (std::rand() % 12), 7 + (std::rand() % 3)),
        Enemy("Skeleton", 45 + (std::rand() % 15), 8 + (std::rand() % 4)),
        Enemy("Dungeon Boss", 70 + (std::rand() % 20), 12 + (std::rand() % 6))
    };

    std::cout << "\nStarting run with " << hero->getName()
              << " the " << hero->getClassName() << ".\n";

    for (size_t room = 0; room < enemies.size(); ++room) {
        Enemy enemy = enemies[room];
        std::cout << "\nRoom " << room + 1 << ": " << enemy.getName()
                  << " appears with " << enemy.getHealth() << " HP.\n";

        while (enemy.isAlive() && hero->isAlive()) {
            std::cout << "\n" << hero->getName() << " HP: "
                      << hero->getHealth() << "/" << hero->getMaxHealth()
                      << " | Potions: " << hero->getPotions() << '\n';
            std::cout << enemy.getName() << " HP: " << enemy.getHealth() << '\n';
            std::cout << "1. Basic attack\n";
            std::cout << "2. Special ability\n";
            std::cout << "3. Use potion\n";

            int action = InputHelper::readIntInRange(1, 3);

            if (action == 1) {
                int damage = hero->attack(enemy);
                std::cout << hero->getName() << " deals " << damage << " damage.\n";
            } else if (action == 2) {
                std::cout << hero->useAbility(enemy) << '\n';
            } else {
                if (hero->getPotions() <= 0) {
                    std::cout << "No potions left.\n";
                    continue;
                }
                hero->usePotion();
                std::cout << hero->getName() << " uses a potion and restores health.\n";
            }

            if (enemy.isAlive()) {
                int incomingDamage = enemy.getDamage() + (std::rand() % 5);
                hero->takeDamage(incomingDamage);
                std::cout << enemy.getName() << " hits back for "
                          << incomingDamage << " damage.\n";
            }
        }

        if (!hero->isAlive()) {
            hero->addDeath();
            std::cout << "\n" << hero->getName() << " was defeated.\n";
            hero->setHealth(hero->getMaxHealth());
            hero->setPotions(3);
            std::cout << "The hero is restored at camp for the next run.\n";
            return;
        }

        std::cout << enemy.getName() << " defeated!\n";

        if (room < enemies.size() - 1) {
            int recovery = 8 + (std::rand() % 8);
            hero->heal(recovery);
            std::cout << hero->getName() << " catches a breath and restores "
                      << recovery << " HP.\n";
        }
    }

    hero->addWin();
    hero->setPotions(3);
    std::cout << "\nRun complete! " << hero->getName()
              << " clears the dungeon and earns a win.\n";
}

void Game::saveGame() const {
    if (roster.empty()) {
        throw GameException("Nothing to save. Create a character first.");
    }

    SaveManager::saveCharacters(roster, saveFile);
    std::cout << "Roster saved to " << saveFile << ".\n";
}

void Game::loadGame() {
    roster = SaveManager::loadCharacters(saveFile);
    activeIndex = roster.empty() ? -1 : 0;
    std::cout << "Roster loaded from " << saveFile << ".\n";
}

void Game::removeCharacter() {
    if (roster.empty()) {
        throw GameException("No characters to remove.");
    }

    viewRoster();
    std::cout << "Choose the character to remove:\n";
    int choice = InputHelper::readIntInRange(1, static_cast<int>(roster.size()));
    int removedIndex = choice - 1;
    std::string removedName = roster[removedIndex]->getName();

    roster.erase(roster.begin() + removedIndex);

    if (roster.empty()) {
        activeIndex = -1;
    } else if (activeIndex == removedIndex) {
        activeIndex = 0;
    } else if (activeIndex > removedIndex) {
        --activeIndex;
    }

    std::cout << removedName << " was removed from the roster.\n";
}

void Game::run() {
    displayWelcome();

    bool running = true;
    while (running) {
        try {
            displayMainMenu();
            int choice = InputHelper::readIntInRange(1, 8);

            switch (choice) {
                case 1:
                    createCharacter();
                    break;
                case 2:
                    chooseActiveCharacter();
                    break;
                case 3:
                    startRun();
                    break;
                case 4:
                    viewRoster();
                    break;
                case 5:
                    saveGame();
                    break;
                case 6:
                    loadGame();
                    break;
                case 7:
                    removeCharacter();
                    break;
                case 8:
                    running = false;
                    std::cout << "Goodbye.\n";
                    break;
                default:
                    throw GameException("Unknown menu choice.");
            }
        } catch (const GameException& exception) {
            std::cout << "Error: " << exception.what() << '\n';
        } catch (const std::exception& exception) {
            std::cout << "Unexpected error: " << exception.what() << '\n';
        }
    }
}
