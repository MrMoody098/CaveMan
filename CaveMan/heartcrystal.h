#ifndef HEARTCRYSTAL_H
#define HEARTCRYSTAL_H

#include "item.h"
#include "player.h"

// Definition of BitStructure

class HeartCrystal : public Item  {
public:
    // Constructor
    HeartCrystal(Player& player);
    // Override the use function to add health
    void use() override;
    Player& getPlayer();

private:
    Player& player;

};

#endif // HEARTCRYSTAL_H

