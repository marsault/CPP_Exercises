#pragma once

#include <iostream>
#include <unordered_map>

class Material
{
    // Affiche le nom d'un materiau.
    friend std::ostream &operator<<(std::ostream &stream, const Material &material) { return stream << material._name; }

public:
    Material(std::string name) : _name{std::move(name)} { std::cerr << "Material <" << *this << "> was created." << std::endl; }

    const std::string &name() const { return _name; }

    ~Material() { std::cerr << "Material <" << *this << "> was deleted." << std::endl; }

private:
    std::string _name;
};
