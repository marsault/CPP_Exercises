#pragma once

#include <iostream>
#include <string>
#include <utility>

class Material
{
  // Affiche le nom d'un matériau
  friend std::ostream& operator<<(std::ostream& stream, const Material& material)
  {
    return stream;
  }
};
