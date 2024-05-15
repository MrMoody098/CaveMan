#ifndef SKIPSTONE_H
#define SKIPSTONE_H
#include "item.h"
#include "player.h"
class SkipStone :public Item
{
public:
    SkipStone(Player& player) ;
    // Override the use function to add health
    void use() override;
    Player& getPlayer();
private:
    Player& player;
};

#endif // SKIPSTONE_H
