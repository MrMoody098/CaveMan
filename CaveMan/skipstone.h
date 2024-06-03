#ifndef SKIPSTONE_H
#define SKIPSTONE_H

#include "item.h"

class MainWindow; // Forward declaration
using namespace interactable;
class SkipStone : public Item {
public:
    SkipStone(bool &fightOver,MainWindow* mainWindow); // Constructor to initialize fightOver
    ~SkipStone();

    SkipStone(const SkipStone& other); // Copy constructor
    SkipStone& operator=(const SkipStone& other); // Assignment operator

    void use() override; // No need to pass fightOver as an argument here

private:
    bool &fightOver; // Member variable to store the reference to fightOver
    MainWindow* mainWindow; // Store the MainWindow pointer


};

#endif // SKIPSTONE_H
