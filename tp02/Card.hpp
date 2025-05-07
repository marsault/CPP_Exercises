#include <ostream>
#include <string>
#pragma once

enum class CardColor
{
    Coeur   = 1,
    Pique   = 2,
    Carreau = 3,
    Trefle  = 4
};

enum class CardValeur
{
    Sept  = 7,
    Huit  = 8,
    Neuf  = 9,
    Dix   = 10,
    Valet = 11,
    Dame  = 12,
    Roi   = 13,
    As    = 14
};

class Card
{
public:

    Card(CardValeur value, CardColor color);

    Card(unsigned int value, unsigned int color);

    void print() const;

    friend std::ostream& operator<<(std::ostream& stream, Card card);

    bool operator==(Card other) const;

    bool operator<(Card other) const;

private:
    CardValeur _value;
    CardColor  _color;
    static std::string string_from_color(CardColor color);

    static std::string string_from_value(CardValeur value);
};