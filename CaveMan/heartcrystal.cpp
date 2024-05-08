#include "heartcrystal.h"

// Constructor implementation
HeartCrystal::HeartCrystal(Player& player) : Item(5, "Gives Player +1 HP"), player(player) {
    // Initialize 'player' using the member initializer syntax
}

// Override the use function implementation
void HeartCrystal::use() {
    // Access 'player' using the dot operator and call 'addHealth' function
    if(bitStruct.quantity>0) {player.addHealth(1);bitStruct.quantity-=1;}
}

// Method to set values for bitStructure
void HeartCrystal::setValues(int quantity, int value, int isConsumable) {
    bitStruct.quantity = quantity;
    bitStruct.value = value;
    bitStruct.isConsumable = isConsumable;
}

Player& HeartCrystal::getPlayer(){return player;}

int HeartCrystal::getQuantity(){return bitStruct.quantity;}

int HeartCrystal::getValue(){return bitStruct.quantity;}

