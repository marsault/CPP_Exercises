#pragma once

#include <ostream>
#include "Material.hpp"

class Recipe
{
    // Affiche l'identifiant et la formule d'une recette.
    friend std::ostream &operator<<(std::ostream &stream, const Recipe &recipe) { return stream; }

public:
    Recipe(MaterialBag requirements, const Material *product) : _requirements{std::move(requirements)}, _product{product}
    {
        std::cout << std::endl;
    }

private:
    MaterialBag _requirements;
    const Material *_product;
    size_t _id = ++_next_id;
    static inline size_t _next_id = 0;
};
