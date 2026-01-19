#include "Value.hpp"

#include <iostream>


std::vector<Value> all_values_init() 
{
    std::vector<Value> res;
    for (unsigned i=2; i<=14u; ++i)
        res.push_back(static_cast<Value>(i));
    return res;
}


const std::vector<Value> all_values = all_values_init();

std::ostream& operator<<(std::ostream& o, Value c) {
    switch (c) {
        case Value::As: return o << "As";
        case Value::Roi: return o << "Roi";
        case Value::Dame: return o << "Dame";
        case Value::Valet: return o << "Valet";
        default: return o << static_cast<unsigned>(c);
    }
}

// Après les questions bonus de Card
void print(Value v) {
    std::cout << v;
}

// Avant les questions bonus de Card
// void print(Value v) {
//     std::cout << static_cast<unsigned>(v);
// }