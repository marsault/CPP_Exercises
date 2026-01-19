#pragma once

#include <iostream>
#include <vector>


//   vvvvv   Ne pas oublier le 'class', on utile des enum C++ !
enum class Color {
    Pique,
    Coeur,
    Carreau,
    Trefle
};

void print(Color c);

std::ostream& operator<<(std::ostream&, Color);

//vvvv Le mot-clef 'extern" est nécessaire pour indiquer qu'on l'initialise dans le .hpp
extern const std::vector<Color> all_colors;