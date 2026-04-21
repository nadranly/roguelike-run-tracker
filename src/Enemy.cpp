#include "Enemy.h"

Enemy::Enemy() : name("Unknown"), health(1), damage(1) {}

Enemy::Enemy(const std::string& name, int health, int damage)
    : name(name), health(health), damage(damage) {}

const std::string& Enemy::getName() const {
    return name;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getDamage() const {
    return damage;
}

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

bool Enemy::isAlive() const {
    return health > 0;
}
