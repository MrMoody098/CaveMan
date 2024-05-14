#ifndef ITEM_H
#define ITEM_H

#include <QMainWindow>

struct BitStructure {
    int quantity: 10; // store up to 7 in quantity
    int value: 10;    // store our value of 15
    int isConsumable: 1; // stores isConsumable check
    int id: 3; //store id up to 7
};

class Item
{
public:
    // Constructor
    Item( int value,QString description,QString name,int quantity,int id,int isConsumable);
    //Release Memeory using descturctor

    int getValue();
    QString getDescription();
    int getQuantity();
    void incQuantity();
    void decQuantity();
    int getId();
    QString getName();
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
