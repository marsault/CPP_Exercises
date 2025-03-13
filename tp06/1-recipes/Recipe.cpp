#include "Recipe.hpp"

size_t Recipe::_currentSize = 1;

Recipe::Recipe(std::vector<std::string> materials, std::vector<std::string> products)
    : _materials { std::move(materials) }
    , _products { std::move(products) }
    , _id { _currentSize++ } {
}

std::ostream& operator<<(std::ostream& stream, const Recipe& recipe) {
    stream << "(" << recipe._id << ") ";
    for (const auto& material : recipe._materials)
    {
        stream << material << " ";
    }
    stream << "=> ";
    for (const auto& product : recipe._products)
    {
        stream << product << " ";
    }
    return stream;
}

const std::vector<std::string>& Recipe::get_materials() const {
    return _materials;
}

const std::vector<std::string>& Recipe::get_products() const {
    return _products;
}

size_t Recipe::get_id() const {
    return _id;
}