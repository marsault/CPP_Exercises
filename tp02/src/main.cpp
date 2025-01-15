#include "Card.hpp" // Card
#include <iostream> // cout

int main() {
    // test basique
    const Card c1 { 8, "Pique" };
    c1.print();

    // test de ==
    const Card c2 { 8, "Pique" };
    std::cout << (c2 == c1) << std::endl; // -> 1
    c2.print();
    const Card c3 { 10, "Carreau" };
    std::cout << (c2 == c3) << std::endl; // -> 0 
    c3.print();

    // test de <
    std::cout << (c1 < c2) << std::endl; // -> 0
    std::cout << (c1 < c3) << std::endl; // -> 1
    std::cout << (c3 < c1) << std::endl; // -> 0

    // test bonus print
    std::cout << "Test du bonus (print)" << std::endl;
    for(unsigned i: {11, 12, 13, 14}) {
        const Card c { i, "Carreau" };
        c.print();
    }

    // test bonus opérateur << 
    std::cout << "Test du bonus (<<)" << std::endl;
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c3: " << c3 << std::endl;
    
}
