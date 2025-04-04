#pragma once
#include "Tracker.hpp"

#include <string>
class Card
{
private:
    unsigned    _value;
    std::string _color;
    Tracker     tracker;

public:
    // ==========================================
    // IL EST INTERDIT DE MODIFIER LES
    // CONSTRUCTEURS DE COPIE ET DE DEPLACEMENT.
    // ==========================================

    Card(unsigned, const std::string&);

    void print() const;
    bool operator==(Card) const;
    bool operator<(Card) const;

    friend std::ostream& operator<<(std::ostream&, Card);
};
