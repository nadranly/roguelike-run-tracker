#include "Mage.h"
#include <cstdlib>
#include <string>

Mage::Mage(const std::string& name)
    : Character(name, 95, 16) {}

std::string Mage::getClassName() const {
    return "Mage";
}

int Mage::attack(Enemy& enemy) {
    int damage = baseDamage + (std::rand() % 12);
    enemy.takeDamage(damage);
    return damage;
}

std::string Mage::useAbility(Enemy& enemy) {
    int spellDamage = 22 + (std::rand() % 18);
    enemy.takeDamage(spellDamage);
    return name + " uses Arc Burst for " + std::to_string(spellDamage) + " damage.";
}

Character* Mage::clone() const {
    return new Mage(*this);
}
