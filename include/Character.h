#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Enemy.h"

class Character {
protected:
    std::string name;
    int maxHealth;
    int health;
    int baseDamage;
    int wins;
    int deaths;
    int runsPlayed;
    int potions;

public:
    Character(const std::string& name, int maxHealth, int baseDamage);
    virtual ~Character() = default;

    const std::string& getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getBaseDamage() const;
    int getWins() const;
    int getDeaths() const;
    int getRunsPlayed() const;
    int getPotions() const;

    void setHealth(int value);
    void setWins(int value);
    void setDeaths(int value);
    void setRunsPlayed(int value);
    void setPotions(int value);

    void heal(int amount);
    void takeDamage(int amount);
    bool isAlive() const;
    void usePotion();

    void addWin();
    void addDeath();
    void addRun();

    virtual std::string getClassName() const = 0;
    virtual int attack(Enemy& enemy) = 0;
    virtual std::string useAbility(Enemy& enemy) = 0;
    virtual Character* clone() const = 0;
};

#endif
