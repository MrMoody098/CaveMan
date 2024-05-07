#ifndef HEARTCRYSTAL_H
#define HEARTCRYSTAL_H

#include "item.h"

class HeartCrystal : public Item {
public:
    // Constructor
    HeartCrystal();

    // Override the use function to add health
    void use() override;
};

#endif // HEARTCRYSTAL_H
