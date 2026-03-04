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
    {}

    int get_x() const { return _x; }
    int get_y() const { return _y; }

    // virtual /* <- question B.3 */ char get_representation() const { return '?'; }
    virtual char get_representation() const = 0; // question C.5

    virtual /* <- question C.2 */
    void update(int width, int height) {
        random_move(_x, _y);
        // question B.6
        if (_x < 0) _x = 0;
        if (_y < 0) _y = 0;
        if (_x >= width) _x = width - 1;
        if (_y >= height) _y = height - 1;
    }
    // question D.1: la ligne suivante suffit à faire compiler le code en décommentant les deux
    // lignes de trigger_interactions; il faut bien veiller à passer Entity par référence, car
    // la présence de la fonction virtuelle empêche la construction d'une copie d'Entity et donc
    // aussi le passage par valeur puisqu'il implique une copie
    virtual void interact_with(Entity& entity) {}

    // question E.1
    virtual bool should_destroy() const { return false; }

    virtual ~Entity() {}; // question E.4

private:
    int _x = 0;
    int _y = 0;
};
