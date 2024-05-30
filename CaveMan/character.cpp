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
// Operator overload for adding an item to the inventory
Character& Character::operator+(Item* newItem) {
    this->addItem(newItem);
    return *this;
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
    Item* inv= getItem(newItem->getId());
    if(inv){
        inv->setQuantity( (newItem->getQuantity()) +(inv->getQuantity()) );

    }
    else{ items.push_back(newItem); };
}

void Character::removeItem(int id) {
    for(auto iter = items.begin(); iter != items.end(); ++iter){
        if((*iter)->getId() == id){
            delete *iter; // Free memory of the item being removed
            items.erase(iter); // Remove the item from the vector
            return;
        }
    }
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

