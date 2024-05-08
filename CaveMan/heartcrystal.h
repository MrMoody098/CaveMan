#ifndef HEARTCRYSTAL_H
#define HEARTCRYSTAL_H

#include "item.h"
#include "player.h"
// Definition of BitStructure
struct BitStructure {
    int quantity: 3; // store up to 8 in quantity
    int value: 3;    // store our value of 8
    int isConsumable: 1; // stores isConsumable check
};

class HeartCrystal : public Item {
public:
    // Constructor
    HeartCrystal(Player& player);
    void setValues(int quantity, int value, int isConsumable);
    // Override the use function to add health
    void use() override;
    Player& getPlayer();
    int getQuantity();
    int getValue();

private:
    BitStructure bitStruct;
    Player& player;

};

#endif // HEARTCRYSTAL_H

