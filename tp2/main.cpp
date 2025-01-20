#include "Card.hpp"
#include "Player.hpp"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono_literals;

    const Card c1 {8, "Pique"};
    c1.print();

    const Card c2 {8, "Carreau"};
    std::cout << (c2 == c1) << std::endl; // -> 1
    const Card c3 {10, "Carreau"};
    std::cout << (c2 == c3) << std::endl; // -> 0

    std::cout << (c1 < c2) << std::endl; // -> 0
    std::cout << (c1 < c3) << std::endl; // -> 1
    std::cout << (c3 < c1) << std::endl; // -> 0

    Player p1{"Gerald"};
    Player p2{"Julien"};
    Player::deal_all_cards(p1, p2);

    while (!Player::play(p1, p2)) {
        std::this_thread::sleep_for(2s);
    }

    std::cout << "\nCartes de Gerald :" << std::endl;
    for (std::size_t i = 0; i < p1.get_cards().size(); ++i) {
        p1[i].print();
    }

    std::cout << "\nCartes de Julien :" << std::endl;
    for (std::size_t i = 0; i < p2.get_cards().size(); ++i) {
        p2[i].print();
    }

    std::cout << "\nRésultats finaux :" << std::endl;
    std::cout << "Gerald a obtenu " << p1.get_score() << " points." << std::endl;
    std::cout << "Julien a obtenu " << p2.get_score() << " points." << std::endl;

    if (p1.get_score() > p2.get_score()) {
        std::cout << "Gerald remporte la partie !" << std::endl;
    } else if (p1.get_score() < p2.get_score()) {
        std::cout << "Julien remporte la partie !" << std::endl;
    } else {
        std::cout << "La partie se termine par une égalité !" << std::endl;
    }

    return 0;
}