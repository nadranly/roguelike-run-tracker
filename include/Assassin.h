#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "Character.h"

class Assassin : public Character {
public:
    explicit Assassin(const std::string& name);

    std::string getClassName() const override;
    int attack(Enemy& enemy) override;
    std::string useAbility(Enemy& enemy) override;
    Character* clone() const override;
};

#endif
