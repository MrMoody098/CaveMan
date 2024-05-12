#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <vector> // Include vector header for std::vector
#include <item.h> // Forward declaration of Item class
#include "enemy.h"
class Room
{
public:
    Room(QString name);
    const QString getName();
    const QString getDescription();
    void setExits(Room* North, Room* East, Room* South, Room* West);
    bool enemyInRoom();
    Item* getItem(int id);
    int getNumItems();
    void setEnemy(Enemy* enemy);
    Enemy* getEnemy();
    void addItem(Item* newItem);
    std::vector<Item*> getItems();
    Room* getNorth();
    Room* getSouth();
    Room* getEast();
    Room* getWest();

    void addItem(Item item);
    void removeItem(Item* item);
    void setDescription(QString description);
    QString itemListToQString();

private:
    QString description;
    QString name;
    Room* North;
    Room* East;
    Room* South;
    Room* West;
    std::vector<Item*> items;
    Enemy* enemy;
};

#endif // ROOM_H
