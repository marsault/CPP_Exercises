#include <string>   // string

class Card
{
private:
    unsigned _value;
    std::string _color;

public:
    Card(unsigned, std::string);
    ~Card();

    void print() const ;                    // const nécessaire pour la question 6 de Card
    bool operator== (const Card) const ;    // les DEUX const sont nécessaires pour la question 8 de Card
    bool operator< (const Card) const ;     // const: cf opérateur ==

    /*
        Bonus 11: friend est nécessaire pour autoriser << à accéder aux membres privés de Card; 
        les & sont indispensables pour permettre la modification du flux par <<; const est là pour
        les mêmes raisons que ci-dessus.
    */
    friend std::ostream& operator<<(std::ostream&, const Card&);

    // TODO: bonus enum class
};
