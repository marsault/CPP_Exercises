#include "Card.hpp"

#include <iostream>

Card::Card(CardValeur value, CardColor color)
    : _value { value }
    , _color { color } {
}

Card::Card(unsigned int value, unsigned int color)
    : Card{static_cast<CardValeur>(value), static_cast<CardColor>(color)} {
        
}

void Card::print() const {
    std::cout << Card::string_from_value(_value) << " de " << Card::string_from_color(_color) << std::endl;
}

std::string Card::string_from_color(CardColor color) {
    switch (color)
    {
    case CardColor::Coeur:
        return "Coeur";
    case CardColor::Carreau:
        return "Carreau";
    case CardColor::Trefle:
        return "Trefle";
    case CardColor::Pique:
        return "Pique";
    default:
        return "?";
    }
}

std::string Card::string_from_value(CardValeur value) {
    switch (value)
    {
    case CardValeur::As:
        return "AS";
    case CardValeur::Roi:
        return "Roi";
    case CardValeur::Dame:
        return "Dame";
    case CardValeur::Valet:
        return "Valet";
    default:
        return std::to_string(static_cast<int>(value));
    }
}

std::ostream& operator<<(std::ostream& stream, Card card) {
    return stream << Card::string_from_value(card._value) << " de " << Card::string_from_color(card._color);
}

bool Card::operator==(Card other) const {
    return _value == other._value;
}

bool Card::operator<(Card other) const {
    return _value < other._value;
}