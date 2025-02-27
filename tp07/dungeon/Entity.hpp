#pragma once

#include "Random.hpp"

class Entity
{
public:
    Entity() = default;

    Entity(int x, int y)
        : _x { x }
        , _y { y }
    {}

    int get_x() const { return _x; }
    int get_y() const { return _y; }

    // virtual /* <- question B.3 */ char get_representation() const { return '?'; } 
    virtual char get_representation() const = 0; // question C.5

    virtual /* <- question C.2 */ void update() { random_move(_x, _y); }
    // question D.1: la ligne suivante suffit à faire compiler le code en décommentant les deux 
    // lignes de trigger_interactions; il faut bien veiller à passer Entity par référence, car
    // la présence de la fonction virtuelle empêche la construction d'une copie d'Entity et donc
    // aussi le passage par valeur puisqu'il implique une copie
    virtual void interact_with(Entity& entity) {};

private:
    int _x = 0;
    int _y = 0;
};
