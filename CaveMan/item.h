#ifndef ITEM_H
#define ITEM_H

#include <QMainWindow>

struct BitStructure {
    int quantity: 3; // store up to 7 in quantity
    int value: 4;    // store our value of 15
    int isConsumable: 1; // stores isConsumable check
};

class Item
{
public:
    // Constructor
    Item( int value,QString description,QString name,int quantity);
    int getValue();
    int getDescription;
    int getQuantity();
    void isConsumable();
    void notConsumable();
    void setValue(int);
    void setValues(int quantity, int value, int isConsumable);
    void setQuantity(int quantity);

    virtual void use();

    // Override the use function to add health
    //as we want subclasses to accesses but also encaptulate
private:
    QString description;
    QString name;

protected:
    BitStructure bitStruct;
};
#endif // ITEM_H
