#pragma once

#include "Entity.hpp"

class Item :public Entity
{
private:
    /* data */
public:
    Item(int width, int height) : Entity {random_value(0, width -1), random_value(0, height -1)}{
    }

    void update() override{}
};

