#ifndef ITEM_H
#define ITEM_H

#include <QMainWindow>
class Item
{
public:
    Item(unsigned int value,QString description);
    unsigned int getValue();
    unsigned int getDescription;
    virtual void use();

private:
    unsigned int value;
    QString description;
};

#endif // ITEM_H
