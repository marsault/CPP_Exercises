#pragma once

#include "Random.hpp"
#include "Logger.hpp"
class Entity
{
public:
    Entity() = default;

    Entity(int x, int y)
        : _x { x }
        , _y { y }
    {logger << "Hello world" << std::endl;}

    int get_x() const { return _x; }
    int get_y() const { return _y; }

    char get_representation() const { return '?'; }

    void update() { 
        random_move(_x, _y); 
        logger << "Updated " << this << std::endl;
    }

private:
    int _x = 0;
    int _y = 0;
};
