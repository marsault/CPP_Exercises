#include "Color.hpp"

const std::vector<Color> all_colors = {Color::Pique, Color::Coeur, Color::Carreau, Color::Trefle};



// Avant les questions bonus de Card.
// void print(Color c) {
//     switch (c) {
//         case Color::Carreau: std::cout << "Carreau"; break;
//         case Color::Trefle: std::cout << "Trefle"; break;
//         case Color::Coeur: std::cout << "Coeur"; break;
//         case Color::Pique: std::cout << "Pique"; break;
//     }
// }

// Après les questions bonus de Card.
void print(Color c) {
    std::cout << c;
}





std::ostream& operator<<(std::ostream& o, Color c) {
    switch (c) {
        case Color::Carreau: return o << "Carreau";
        case Color::Trefle: return o << "Trefle";
        case Color::Coeur: return o << "Coeur";
        case Color::Pique: return o << "Pique";
    }
    return o; // intuile, mais le compilateur en as besoin.
}
