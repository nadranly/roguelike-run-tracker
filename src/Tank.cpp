#include "Tank.h"
#include <cstdlib>
#include <string>

Tank::Tank(const std::string& name)
    : Character(name, 130, 14) {}

std::string Tank::getClassName() const {
    return "Tank";
}

int Tank::attack(Enemy& enemy) {
    int damage = baseDamage + (std::rand() % 7);
    enemy.takeDamage(damage);
    return damage;
}

std::string Tank::useAbility(Enemy& enemy) {
    int slamDamage = 18 + (std::rand() % 8);
    enemy.takeDamage(slamDamage);
    heal(12);
    return name + " uses Iron Slam for " + std::to_string(slamDamage) +
           " damage and restores 12 health.";
}

Character* Tank::clone() const {
    return new Tank(*this);
}
