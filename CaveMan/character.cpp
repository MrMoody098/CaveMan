#include "character.h"

// Member function implementations
int Character::getHealth() {
    return health;
}

void Character::setHealth(int newHealth) {
    health = newHealth;
}

void Character::addHealth(int amount) {
    health += amount;
}

void Character::subtractHealth(int amount) {
    if (amount <= health) {
        health -= amount;
    } else {
        health = 0;
    }
}

Item* Character::getItem(int id){
    for(Item* i:items){
        if (i->getId() ==id){
            return i;
        }
    }
    //return 0 if item was not found
    return 0;
}

void Character::addItem(Item* newItem) {
    if(getItem(newItem->getId())){ getItem(newItem->getId())->incQuantity(); }
    else{ items.push_back(newItem); };
}

int Character::getNumItems() {
    return items.size();
}

void Character::addCoins(int coins){
    this->coins+=coins;
}

int Character::getCoins(){
    return coins;
}
std::vector<Item*> Character:: getItems(){
    return items;
}

