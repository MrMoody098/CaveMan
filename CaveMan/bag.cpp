#ifndef BAG_H
#define BAG_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "item.h"
#include "Container.h"



// Template bag item
template <typename T>
class Bag : public Item, public Container {
public:
    Bag(int value, QString description, QString name, int quantity, int id, int isConsumable)
        : Item(value, description, name, quantity, id, isConsumable) {}

    void add(const T& item) override;
    void remove(const T& item) override;
    bool contains(const T& item) const override;
    void clear() override;
    size_t size() const override;
    void print() const override;

private:
    std::vector<T> items;
};

template <typename T>
void Bag<T>::add(const T& item) {
    items.push_back(item);
}

template <typename T>
void Bag<T>::remove(const T& item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    }
}

template <typename T>
bool Bag<T>::contains(const T& item) const {
    return std::find(items.begin(), items.end(), item) != items.end();
}

template <typename T>
void Bag<T>::clear() {
    items.clear();
}

template <typename T>
size_t Bag<T>::size() const {
    return items.size();
}

template <typename T>
void Bag<T>::print() const {
    for (const auto& item : items) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

#endif // BAG_H
