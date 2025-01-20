#pragma once
#include <string>
#include <iostream>

class Card {
    public:
        Card(unsigned int value, std::string _color);
        void print() const;

        int operator==(const Card& c1) const {
            return (_value == c1._value) ? 1 : 0;
        }

        int operator<(const Card& c2) const {
            return (_value < c2._value) ? 1 : 0;
        }

    private:
        unsigned int _value;
        std::string _color;
};