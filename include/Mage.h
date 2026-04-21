#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage : public Character {
public:
    explicit Mage(const std::string& name);

    std::string getClassName() const override;
    int attack(Enemy& enemy) override;
    std::string useAbility(Enemy& enemy) override;
    Character* clone() const override;
};

#endif
