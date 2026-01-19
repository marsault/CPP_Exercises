#pragma once

#include <iostream>
#include <vector>


//   vvvvv   Ne pas oublier le 'class', on utile des enum C++ !
enum class Value : unsigned {
    Deux=2,
    Trois,
    Quatre,
    Cinq,
    Six,
    Sept,
    Huit,
    Neuf,
    Dix,
    Valet,
    Dame,
    Roi,
    As,
};

std::ostream& operator<<(std::ostream&, Value);
void print(Value c);


//vvvv Le mot-clef 'extern" est nécessaire pour indiquer qu'on l'initialise dans le .hpp
extern const std::vector<Value> all_values;