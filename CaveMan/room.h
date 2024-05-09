#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <vector> // Include vector header for std::vector
#include <item.h> // Forward declaration of Item class
#include <Character.h> // Forward declaration of Character class

class Room
{
public:
    Room(QString name);
    const QString getName();
    const QString getDescription();
    void setExits(Room* North, Room* East, Room* South, Room* West);
    std::vector<Item> getItemsInRoom();
    std::vector<Character> getCharsInRoom();
    Room* getNorth();
    Room* getSouth();
    Room* getEast();
    Room* getWest();

    void addItem(Item item);
    void removeItem(Item* item);
    void setDescription(QString description);

private:
    QString description;
    QString name;
    Room* North;
    Room* East;
    Room* South;
    Room* West;
    std::vector<Item> itemList;
    std::vector<Character> characterList;
};

#endif // ROOM_H
