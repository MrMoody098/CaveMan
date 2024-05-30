#include "skipstone.h"
#include "mainwindow.h"

SkipStone::SkipStone(bool &fightOverRef, MainWindow* mainWindow)
    : Item(5, "Allows Player to Skip a fight", "SkipStone", 1, 2, 1), fightOver(fightOverRef), mainWindow(mainWindow) {}

SkipStone::SkipStone(const SkipStone& other)
    : Item(other), fightOver(other.fightOver), mainWindow(other.mainWindow) {}

SkipStone& SkipStone::operator=(const SkipStone& other) {
    if (this != &other) {
        Item::operator=(other);
        fightOver = other.fightOver;
        mainWindow = other.mainWindow;
    }
    return *this;
}

SkipStone::~SkipStone() {}

void SkipStone::use() {
    // When there is a SkipStone in inventory
    if (bitStruct.quantity > 0) {
        // SKIP FIGHT/WIN AUTOMATICALLY
        fightOver = true;
        // Decrement quantity
        bitStruct.quantity -= 1;

        // Call enemyDead() from MainWindow
        if (mainWindow) {
            mainWindow->enemyDead();
        }
    }
}
