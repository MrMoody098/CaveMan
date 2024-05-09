#include "item.h"

Item::Item(int value, QString description,QString name,int quantity){
    this->setValue(value);
    this->description = description;
    this->name =name;
    this->setQuantity(quantity);
}


int Item::getValue() {
    return bitStruct.value;
}
void Item::setValue(int value) {
     bitStruct.value =value;
}

void Item::setQuantity(int quantity){
    bitStruct.quantity= quantity;
};
int Item::getQuantity(){
    return bitStruct.quantity;
}
void Item::setValues(int quantity, int value, int isConsumable) {
    bitStruct.quantity = quantity;
    bitStruct.value = value;
    bitStruct.isConsumable = isConsumable;
}

void Item::isConsumable(){
    bitStruct.isConsumable = 1;
};
void Item::notConsumable(){
    bitStruct.isConsumable = 0;
};
void Item::use() {
    // Default implementation for using an item
    // This can be overridden by sub classes
};
