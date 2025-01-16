#include <string>
#include "Player.hpp"
#include <random>       // default_random_engine, random_device
#include <algorithm>    // shuffle
#include <iostream>     // cout, endl

Player::Player(const std::string& nom) : _score(0)
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

Card Player::operator[] (const unsigned& i) {
    return _cards[i];
}

bool Player::play(Player& premier, Player& second) {
    premier._cards.pop_back();
    second._cards.pop_back();

    // afficher les deux cartes jouées au tour courant
    std::cout << "Joueur 1 (" << premier._name << "): " << premier._cards.back() << std::endl;
    std::cout << "Joueur 2 (" << second._name << "): " << second._cards.back() << std::endl;

    // mettre à jour les scores
    if(premier._cards.back() < second._cards.back()) {
        std::cout << "Joueur 2 remporte le pli" << std::endl;
        ++second._score;
    }
    else if (second._cards.back() < premier._cards.back()) {
        std::cout << "Joueur 1 remporte le pli" << std::endl;
        ++premier._score;
    }
    else {
        // égalité (bonus 6.1): une seule bataille
        // vérifions d'abord s'il reste des cartes, sinon le comportement de pop_back() est indéfini
        if(premier._cards.empty() and second._cards.empty())
            return true; 

        premier._cards.pop_back();
        second._cards.pop_back();

        if(premier._cards.empty() and second._cards.empty())
            return true; 

        // afficher les deux nouvelles cartes 
        std::cout << "\tJoueur 1 (" << premier._name << "): " << premier._cards.back() << std::endl;
        std::cout << "\tJoueur 2 (" << second._name << "): " << second._cards.back() << std::endl;

        if(premier._cards.back() < second._cards.back()) {
            std::cout << "\tJoueur 2 remporte la bataille" << std::endl;
            second._score += 3;
        }
        else if (second._cards.back() < premier._cards.back()) {
            std::cout << "\tJoueur 2 remporte la bataille" << std::endl;
            premier._score += 3;
        }
        else {
            std::cout << "\tNouvelle égalité, pas de modification des points" << std::endl;
        }
        
    }
    ++turn_number;

    // la partie est finie quand il n'y a plus de cartes
    return not(premier._cards.empty() and second._cards.empty());
}

unsigned int Player::get_score() const {
    return _score;
}
