#pragma once

#include "Item.hpp"
#include "Random.hpp"

class Trap : public Item
{
private:
    /* data */
public:
    Trap(int width, int height) : Item {width, height }{
    }

    char get_representation() const override { return 'X';}
};
