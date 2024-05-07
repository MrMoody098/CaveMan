#include "item.h"

Item::Item(unsigned int value, QString description) : value(value), description(description){}

unsigned int Item::getValue() {
    return value;
}

void Item::use() {
    // Default implementation for using an item
    // This can be overridden by sub classes
}
