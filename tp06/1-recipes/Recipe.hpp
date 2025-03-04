#pragma once

#include <ostream>
#include "Material.hpp"

class Recipe
{
    // Affiche l'identifiant et la formule d'une recette.
    friend std::ostream &operator<<(std::ostream &stream, const Recipe &recipe)
    {
        stream << "(" << recipe._id << ")";
        for (auto &p : recipe._requirements)
        {
            stream << " " << *(p.first);
            if (p.second > 1)
                stream << "[x" << p.second << "]";
        }
        return stream << " => " << *(recipe._product);
    }

public:
    Recipe(MaterialBag requirements, const Material *product)
        : _requirements{std::move(requirements)}, _product{product}
    {
    }

    size_t id() const { return _id; }

    const MaterialBag &requirements() const { return _requirements; }
    const Material *product() const { return _product; }

    bool operator<(const Recipe &other) const { return id() < other.id(); }

    bool operator==(const Recipe &other) const { return id() == other.id(); }

private:
    MaterialBag _requirements;
    const Material *_product;
    size_t _id = ++_next_id;
    static inline size_t _next_id = 0;
};

inline bool operator<(const Recipe &left, size_t right) { return left.id() < right; }
inline bool operator<(size_t left, const Recipe &right) { return left < right.id(); }