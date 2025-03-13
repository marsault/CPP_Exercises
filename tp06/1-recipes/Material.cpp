#include "Material.hpp"

#include <iostream>

Material::Material(std::string name)
    : _name(std::move(name)) {
}

Material::~Material() {
    std::cout << _name << " was destroyed" << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Material& material) {
    stream << material._name;
    return stream;
}

bool Material::operator==(const std::string& other) const {
    return _name == other;
}

const std::string& Material::get_name() const {
    return _name;
}