#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "room.h"
#include "player.h"
#include "item.h"

class GameManager {
public:
    GameManager();
    void setupRooms();
    void initializeGameState(Player& player);
    void updatePlayerStats(Player& player);
    Room* getCurrentRoom();
    void setCurrentRoom(Room* room);
    Room* navigateToRoom(const QString& direction);

private:
    std::vector<Room*> rooms;
    Room* currentRoom;
    Room* lastRoom;
};

#endif // GAMEMANAGER_H
