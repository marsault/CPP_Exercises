#include <string>   // string
#include "Card.hpp" // Card
#include <iostream> // cout
#include <vector>   // vector

Card::Card(Value v, Color c) 
    : _value(v), _color(c)
{}

Card::~Card()
{
}

void Card::print() const {
    // Avant les questions bonus de Card
    // print(_value);
    // std::cout << " de ";
    // print(_color);

    // Après les questions bonus de Card
    std::cout << (*this);
}

bool Card::operator== (const Card& autre) const {
    return _value == autre._value and _color == autre._color;
} 

bool Card::operator< (const Card& autre) const {
    return _value < autre._value;
} 

// Question bonus
std::ostream& operator<<(std::ostream& o, const Card& card) {
    return o << card._value << " de " << card._color;
}
