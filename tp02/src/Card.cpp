#include <string>   // string
#include "Card.hpp" // Card
#include <iostream> // cout
#include <vector>   // vector

// Card bonus (question 10)
const std::vector<std::string> VALEURS = {
    "0", "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As"
};


Card::Card(unsigned v, std::string c)
{
    _value = v;
    _color = c;
}

Card::~Card()
{
}

void Card::print() const {
    std::cout 
        // << _value           // version basique
        << VALEURS[_value]  // version bonus        
        << " de " << _color;
}

bool Card::operator== (const Card autre) const {
    return _value == autre._value and _color == autre._color;
} 

bool Card::operator< (const Card autre) const {
    return _value < autre._value;
} 

// Bonus 11
std::ostream& operator<<(std::ostream& sortie, const Card& carte) {
    sortie << VALEURS[carte._value] << " de " << carte._color;
    return sortie;
}
