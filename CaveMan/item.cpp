#include "item.h"

Item::Item(int value, QString description,QString name,int quantity,int id,int isConsumable){
    this->setValue(value);
    this->description = description;
    this->name =name;
    this->setQuantity(quantity);
    this->bitStruct.id=id;
    this->bitStruct.isConsumable=isConsumable;
}

QString Item:: getName(){
    return this->name;
}
QString Item::getDescription(){
    return this->description;
}

int Item::getId(){
    return bitStruct.id;
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

void Item::incQuantity(){
    bitStruct.quantity++;
}

void Item::decQuantity(){
    if(bitStruct.quantity>0){
    bitStruct.quantity--;
    };
}
void Item::use() {
    // Default implementation for using an item
    // This can be overridden by sub classes
};
