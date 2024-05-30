#include "skipstone.h"

SkipStone::SkipStone(bool &fightOverRef) : Item(5, "Allows Player to Skip a fight", "SkipStone", 1, 2, 1), fightOver(fightOverRef) {}

SkipStone::~SkipStone() {}

void SkipStone::use() {
    // When there is a SkipStone in inventory
    if (bitStruct.quantity > 0) {
        // SKIP FIGHT/WIN AUTOMATICALLY
        fightOver = true;
        // Decrement quantity
        bitStruct.quantity -= 1;
    }
}
