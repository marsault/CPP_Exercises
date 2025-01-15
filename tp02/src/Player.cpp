#include <string>
#include "Player.hpp"
#include <random>       // default_random_engine, random_device
#include <algorithm>    // shuffle
#include <iostream>     // cout, endl

Player::Player(std::string nom) : _score(0)
{
    _name = nom;
}

Player::~Player()
{

}

void Player::deal_all_cards(Player& premier, Player& second) {
    // initialiser toutes les cartes
    std::vector<Card> all_cards;
    for(int valeur=1; valeur<=13; ++valeur)
        for(const auto& couleur: {"Coeur", "Pique", "Trèfle", "Carreau"})
            all_cards.emplace_back(valeur, couleur);

    // mélanger le paquet
    std::random_device rd;
    std::shuffle(all_cards.begin(), all_cards.end(), std::default_random_engine(rd()));

    // ajouter la première moitié de all_cards à la main du premier joueur et la seconde moitié
    // à la main du second joueur
    for(int i=0, s=all_cards.size() / 2; i<s; ++i) {
        premier._cards.push_back(all_cards[i]);
        second._cards.push_back(all_cards[i+s]);
    }
}

Card Player::operator[] (unsigned i) {
    return _cards[i];
}

bool Player::play(Player& premier, Player& second) {
    std::vector<Card> cartes { premier._cards.back(), second._cards.back() };
    premier._cards.pop_back();
    second._cards.pop_back();

    // afficher les deux cartes jouées au tour courant
    std::cout << "Joueur 1 (" << premier._name << "): " << cartes[0] << std::endl;
    std::cout << "Joueur 2 (" << second._name << "): " << cartes[1] << std::endl;

    // mettre à jour les scores
    if(cartes[0] < cartes[1]) {
        std::cout << "Joueur 2 remporte le pli" << std::endl;
        ++second._score;
    }
    else if (cartes[1] < cartes[0]) {
        std::cout << "Joueur 1 remporte le pli" << std::endl;
        ++premier._score;
    }
    ++turn_number;

    // la partie est finie quand il n'y a plus de cartes
    return not(premier._cards.empty() and second._cards.empty());
}

unsigned int Player::get_score() const {
    return _score;
}
