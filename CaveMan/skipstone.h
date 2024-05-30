#ifndef SKIPSTONE_H
#define SKIPSTONE_H

#include "item.h"

class SkipStone : public Item {
public:
    SkipStone(bool &fightOver); // Constructor to initialize fightOver
    virtual ~SkipStone();
    void use(); // No need to pass fightOver as an argument here
private:
    bool &fightOver; // Member variable to store the reference to fightOver
};

#endif // SKIPSTONE_H
