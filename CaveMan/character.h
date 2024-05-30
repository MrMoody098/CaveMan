#ifndef CHARACTER_H
#define CHARACTER_H

#include "item.h" // Include the item header file
#include <vector>

class Character {
public:
    virtual ~Character() = default;

    // Pure virtual functions to be implemented by subclasses
    int getHealth();
    void setHealth(int newHealth);
    void addHealth(int amount);
    void subtractHealth(int amount);
    void addItem(Item* newItem);
    int getNumItems();
    void addCoins(int);
    void incCoins(int);
    int getCoins();
    Item* getItem(int id);
    std::vector<Item*> getItems();
    void removeItem(int id);

    Character& operator+(Item* newItem);

protected:
    int health;
    int coins;
    int heartCrystalCount;
    std::vector<Item*> items;

};
#endif // CHARACTER_H
