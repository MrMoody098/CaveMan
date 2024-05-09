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

std::vector<Item> Room::getItemsInRoom()
{
    // Return the items in the room
    return itemList;
}

void Room::addItem(Item item)
{
    // Add an item to the room
    itemList.push_back(item);
}

void Room::removeItem(Item* item)
{
    // Remove an item from the room
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
