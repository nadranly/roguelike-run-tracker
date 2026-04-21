#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
private:
    std::string name;
    int health;
    int damage;

public:
    Enemy();
    Enemy(const std::string& name, int health, int damage);

    const std::string& getName() const;
    int getHealth() const;
    int getDamage() const;

    void takeDamage(int amount);
    bool isAlive() const;
};

#endif
