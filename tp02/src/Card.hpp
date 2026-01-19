#pragma once  // devient nécessaire à partir de la question 5 de Player
#include <string>   // string

#include "Color.hpp"
#include "Value.hpp"

class Card
{
private:
    Value _value;
    Color _color;

public:
    Card(Value, Color);
    ~Card();

    void print() const ;                    // const nécessaire pour la question 7 de Card
    bool operator== (const Card&) const ;    // les DEUX const sont nécessaires pour la question 9 de Card
    bool operator< (const Card&) const ;     // const: cf opérateur ==

    /*
        Bonus 12: friend est nécessaire pour autoriser << à accéder aux membres privés de Card; 
        les & sont indispensables pour permettre la modification du flux par <<; const est là pour
        les mêmes raisons que ci-dessus.
    */
    friend std::ostream& operator<<(std::ostream&, const Card&);

    // TODO: bonus enum class
};
