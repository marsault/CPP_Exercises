#pragma once

#include <ostream>

class Material
{
public:
    // Affiche le nom d'un materiau.
    friend std::ostream& operator<<(std::ostream& stream, const Material& material);

    Material(std::string name);

    ~Material();

    bool operator==(const std::string& other) const;

    const std::string& get_name() const;

private:
    std::string _name;
};
