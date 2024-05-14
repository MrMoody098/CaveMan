#include "skipstone.h"
// Constructor implementation
SkipStone::SkipStone(Player& player) : Item(5, "Allows Player to Skip a fight","SkipStone",1,2,1), player(player) {

}

// Override the use function implementation
void SkipStone::use() {
    // when there is a SkipStone in invetory
    if(bitStruct.quantity>0) {
        //SKIP FIGHT/WIN AUTOMATICALLY

        //Decrement qunatity
        bitStruct.quantity-=1;

    }
}


Player& SkipStone::getPlayer(){return player;}
