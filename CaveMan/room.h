#ifndef ROOM_H
#define ROOM_H

#include <QMainWindow>
#include <vector>
#include <item.h>

class Room
{
public:
    Room();
    const QString getDescription();
    void setExits(Room* North ,Room* East ,Room* South ,Room* West);
    std::vector<Item> getItemsInRoom();
    void addItem(Item item);
    void removeItem(Item* item);
private:
    Room *North;
    Room *East;
    Room *South;
    Room *West;
    std::vector<Item> itemList;
};

#endif // ROOM_H
