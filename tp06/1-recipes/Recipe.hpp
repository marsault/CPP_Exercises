#pragma once

#include <ostream>
#include <string>
#include <vector>

class Recipe
{
public:
    // Affiche l'identifiant et la formule d'une recette.
    friend std::ostream& operator<<(std::ostream& stream, const Recipe& recipe);
    Recipe(std::vector<std::string> materials, std::vector<std::string> products);
    const std::vector<std::string>& get_materials() const;
    const std::vector<std::string>& get_products() const;
    size_t                          get_id() const;

private:
    std::vector<std::string> _materials;
    std::vector<std::string> _products;
    size_t                   _id;
    static size_t            _currentSize;
};
