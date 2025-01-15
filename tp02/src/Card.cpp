#include <string>   // string
#include "Card.hpp" // Card
#include <iostream> // cout

Card::Card(unsigned v, std::string c)
{
    _value = v;
    _color = c;
}

Card::~Card()
{
}

void Card::print() const {
    std::cout << _value << " de " << _color << std::endl;
}

bool Card::operator== (Card autre) {
    std::cout << _value << " vs " << autre._value << ", " << _color << " vs " << autre._color << std::endl; // DEBUG
    return _value == autre._value and _color == autre._color;
} 
