#include "Card.hpp"
#include "Player.hpp"

#include <iostream>
#include <thread>

int main() {
    // const Card c1 { CardValeur::Huit, CardColor::Pique };
    // c1.print();
    // std::cout << c1 << std::endl;
    // const Card c2 { CardValeur::Huit, CardColor::Pique };
    // std::cout << (c2 == c1) << std::endl; // -> 1
    // const Card c3 { CardValeur::Dix, CardColor::Carreau };
    // std::cout << (c2 == c3) << std::endl; // -> 0

    // std::cout << (c1 < c2) << std::endl; // -> 0
    // std::cout << (c1 < c3) << std::endl; // -> 1
    // std::cout << (c3 < c1) << std::endl; // -> 0

    Player p1 { "Val" };
    Player p2 { "Rieu" };
    Player::deal_all_cards(p1, p2);

    // for (auto i = 0; i < 16; ++i)
    // {
    //     p1[i].print();
    //     std::cout << std::endl;
    //     p2[i].print();
    //     std::cout << std::endl;
    // }

    while (!Player::play(p1, p2))
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (p1.get_score() > p2.get_score())
    {
        std::cout << p1.get_name() << " a gagné avec un score de " << p1.get_score() << std::endl;
    }
    else if (p1.get_score() < p2.get_score())
    {
        std::cout << p2.get_name() << " a gagné avec un score de " << p2.get_score() << std::endl;
    }
    else
    {
        std::cout << "C'est une égalité avec un score de " << p1.get_score() << " pour chaque joueur"
                  << std::endl;
    }

    return 0;
}
