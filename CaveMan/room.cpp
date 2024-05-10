#include "room.h"

//we set the exit pointers to null so were not pointing to any random memeory address
Room::Room(QString name) : name(name), North(nullptr), East(nullptr), South(nullptr), West(nullptr) {}

void Room::setExits(Room* North, Room* East, Room* South, Room* West)
{
    // Set the exits of the room
    this->North = North;
    this->East = East;
    this->South = South;
    this->West = West;
}


Enemy* Room::getEnemy(){
    return this->enemy;
}
void Room::setEnemy(Enemy* enemy){
    this->enemy =enemy;
}
std::vector<Item*> Room::getItems()
{
    // Return the items in the room
    return items;
}

Item* Room::getItem(int id){
    for(Item* i:items){
        if (i->getId() ==id){
            return i;
        }
    }
    //return 0 if item was not found
    return 0;
}

void Room::addItem(Item* newItem) {
    if(getItem(newItem->getId())){ getItem(newItem->getId())->incQuantity(); }
    else{ items.push_back(newItem); };
}

int Room::getNumItems() {
    return items.size();
}


void Room::setDescription(QString description){
    this->description = description ;
}
const QString Room::getName(){
    return this->name;
}

const QString Room::getDescription(){
    return this->description;
}

Room* Room::getNorth(){
    return this->North;
}
Room* Room::getEast(){
    return this->East;
}
Room* Room::getSouth(){
    return this->South;
}
Room* Room::getWest(){
    return this->West;
}
