#include "item.h"
#include "itemexception.h".h"

Item::Item(int value, QString description, QString name, int quantity, int id, int isConsumable) {
    if (value < 0) {
        throw InvalidValueException("Value cannot be negative");
    }
    if (quantity < 0) {
        throw InvalidQuantityException("Quantity cannot be negative");
    }
    this->setValue(value);
    this->description = description;
    this->name = name;
    this->setQuantity(quantity);
    this->bitStruct.id = id;
    this->bitStruct.isConsumable = isConsumable;
}

// Shallow copy constructor
Item::Item(const Item& other) {
    this->description = other.description;
    this->name = other.name;
    this->bitStruct = other.bitStruct;
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        this->description = other.description;
        this->name = other.name;
        this->bitStruct = other.bitStruct;
    }
    return *this;
}

// Deep copy constructor
Item::Item(Item* other) {
    this->description = QString(other->description);
    this->name = QString(other->name);
    this->bitStruct.id = other->bitStruct.id;
    this->bitStruct.value = other->bitStruct.value;
    this->bitStruct.quantity = other->bitStruct.quantity;
    this->bitStruct.isConsumable = other->bitStruct.isConsumable;
}

QString Item::getName() {
    return this->name;
}

QString Item::getDescription() {
    return this->description;
}

int Item::getId() {
    return bitStruct.id;
}

int Item::getValue() {
    return bitStruct.value;
}

void Item::setValue(int value) {
    if (value < 0) {
        throw InvalidValueException("Value cannot be negative");
    }
    bitStruct.value = value;
}

void Item::setQuantity(int quantity) {
    if (quantity < 0) {
        throw InvalidQuantityException("Quantity cannot be negative");
    }
    bitStruct.quantity = quantity;
}

int Item::getQuantity() {
    return bitStruct.quantity;
}

void Item::setValues(int quantity, int value, int isConsumable) {
    if (quantity < 0) {
        throw InvalidQuantityException("Quantity cannot be negative");
    }
    if (value < 0) {
        throw InvalidValueException("Value cannot be negative");
    }
    bitStruct.quantity = quantity;
    bitStruct.value = value;
    bitStruct.isConsumable = isConsumable;
}

void Item::incQuantity() {
    bitStruct.quantity++;
}

void Item::decQuantity() {
    if (bitStruct.quantity > 0) {
        bitStruct.quantity--;
    } else {
        throw InvalidQuantityException("Quantity cannot be decreased below zero");
    }
}

void Item::use() {
    // Default implementation for using an item
    // This can be overridden by subclasses
}

