#include <string>

class Card
{
private:
    unsigned _value;
    std::string _color;

public:
    Card(unsigned, std::string);
    ~Card();

    void print() const ; // const nécessaire pour la question 9 de Card
    bool operator== (Card); 

};
