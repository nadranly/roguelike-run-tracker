#ifndef TANK_H
#define TANK_H

#include "Character.h"

class Tank : public Character {
public:
    explicit Tank(const std::string& name);

    std::string getClassName() const override;
    int attack(Enemy& enemy) override;
    std::string useAbility(Enemy& enemy) override;
    Character* clone() const override;
};

#endif
