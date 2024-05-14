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
    Item* inv= getItem(newItem->getId());
    if(inv){
        inv->setQuantity( (newItem->getQuantity()) +(inv->getQuantity()) );

    }
    else{ items.push_back(newItem); };
}
void Character::removeItem(int itemId) {
    qDebug() << "check1";

    // Iterate through the items vector
    for (auto it = items.begin(); it != items.end(); ++it) {
        qDebug() << "check2";

        // Check if the current item's ID matches the specified ID
        if ((*it)->getId() == itemId) {
            qDebug() << "check3";

            // Remove the item from the vector
            items.erase(it); // Remove the item from the vector
            qDebug() << "check4";

            return; // Exit the function after removing the item
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

