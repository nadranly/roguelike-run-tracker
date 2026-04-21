#include "Assassin.h"
#include <cstdlib>
#include <string>

Assassin::Assassin(const std::string& name)
    : Character(name, 85, 18) {}

std::string Assassin::getClassName() const {
    return "Assassin";
}

int Assassin::attack(Enemy& enemy) {
    int damage = baseDamage + (std::rand() % 10);
    bool crit = (std::rand() % 100) < 30;
    if (crit) {
        damage += 18;
    }
    enemy.takeDamage(damage);
    return damage;
}

std::string Assassin::useAbility(Enemy& enemy) {
    int burstDamage = 25 + (std::rand() % 16);
    enemy.takeDamage(burstDamage);
    return name + " uses Shadow Strike for " + std::to_string(burstDamage) + " damage.";
}

Character* Assassin::clone() const {
    return new Assassin(*this);
}
