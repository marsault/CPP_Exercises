#pragma once

#include "Item.hpp"
#include "Random.hpp"

class Potion : public Item
{
private:
    /* data */
public:
    Potion(int width, int height) : Item {width, height }{
    }
    

    char get_representation() const override { return '$';}
};
