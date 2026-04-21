#include "Character.h"

Character::Character(const std::string& name, int maxHealth, int baseDamage)
    : name(name),
      maxHealth(maxHealth),
      health(maxHealth),
      baseDamage(baseDamage),
      wins(0),
      deaths(0),
      runsPlayed(0),
      potions(3) {}

const std::string& Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

int Character::getMaxHealth() const {
    return maxHealth;
}

int Character::getBaseDamage() const {
    return baseDamage;
}

int Character::getWins() const {
    return wins;
}

int Character::getDeaths() const {
    return deaths;
}

int Character::getRunsPlayed() const {
    return runsPlayed;
}

int Character::getPotions() const {
    return potions;
}

void Character::setHealth(int value) {
    if (value < 0) {
        health = 0;
    } else if (value > maxHealth) {
        health = maxHealth;
    } else {
        health = value;
    }
}

void Character::setWins(int value) {
    wins = value;
}

void Character::setDeaths(int value) {
    deaths = value;
}

void Character::setRunsPlayed(int value) {
    runsPlayed = value;
}

void Character::setPotions(int value) {
    potions = value;
}

void Character::heal(int amount) {
    health += amount;
    if (health > maxHealth) {
        health = maxHealth;
    }
}

void Character::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

bool Character::isAlive() const {
    return health > 0;
}

void Character::usePotion() {
    if (potions > 0) {
        --potions;
        heal(25);
    }
}

void Character::addWin() {
    ++wins;
}

void Character::addDeath() {
    ++deaths;
}

void Character::addRun() {
    ++runsPlayed;
}
