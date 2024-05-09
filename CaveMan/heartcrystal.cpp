#include "heartcrystal.h"
#include "consumable.h"
// Constructor implementation
HeartCrystal::HeartCrystal(Player& player) : Item(5, "Gives Player +1 HP","HeartCrystal",1), player(player) {
    isConsumable();

}

// Override the use function implementation
void HeartCrystal::use() {
    // when there is a HeartCrystal in inv, add health and -1 from inv
    if(bitStruct.quantity>0) {player.addHealth(1);bitStruct.quantity-=1;}
}



Player& HeartCrystal::getPlayer(){return player;}
