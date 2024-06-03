#ifndef CONTAINER_H
#define CONTAINER_H

#include <cstddef> // For size_t
#include "item.h"
using namespace interactable;

class Container {
public:
    virtual ~Container() = default; // Virtual destructor for proper cleanup
    virtual void add(const Item& item) = 0;
    virtual void remove(const Item& item) = 0;
    virtual bool contains(const Item& item) const = 0;
    virtual void clear() = 0;
    virtual size_t size() const = 0;
    virtual void print() const = 0;
};

#endif // CONTAINER_H
