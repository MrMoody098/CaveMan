#ifndef BAG_H
#define BAG_H

#include <vector>
#include <iostream>


//template bag item

template <typename T>
class Bag {
public:
    void add(const T& item);
    void remove(const T& item);
    bool contains(const T& item) const;
    void clear();
    size_t size() const;
    void print() const;

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
