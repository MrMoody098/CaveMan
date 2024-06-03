#include "enemy.h"

// Constructor
Enemy::Enemy(QString name,QString description) :name(name),description(description), alive(true) {
}

Enemy::~Enemy() {
    for (Item* item : items) {
        delete item;
    }
    items.clear();
}

// Getter method for name
QString Enemy::getName() {
    return name;
}

// Getter method for description
QString Enemy::getDescription() {
    return description;
}

// Method to check if the enemy is alive
bool Enemy::isAlive() {
    return alive;
}
