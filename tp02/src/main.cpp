#include "Card.hpp" // Card
#include <iostream> // cout

int main() {
    // test basique
    const Card c1 { 8, "Pique" };
    c1.print();

    // test de ==
    Card c2 { 8, "Carreau" };
    std::cout << (c2 == c1) << std::endl; // -> 1
    c2.print();
    Card c3 { 10, "Carreau" };
    std::cout << (c2 == c3) << std::endl; // -> 0 
    c3.print();
}
