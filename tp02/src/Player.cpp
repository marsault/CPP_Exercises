#include <string>
#include "Player.hpp"
#include <random>       // default_random_engine, random_device
#include <algorithm>    // shuffle
#include <iostream>     // cout, endl
#include <thread> // this_thread

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
    for(Value v: all_values)
        for(Color c: all_colors)
            all_cards.emplace_back(v, c);

    // mélanger le paquet
    std::random_device rd;
     std::shuffle(all_cards.begin(), all_cards.end(), std::default_random_engine(rd()));

    // ajouter la première moitié de all_cards à la main du premier joueur et la seconde moitié
    // à la main du second joueur
    for(int i=0, s=all_cards.size() / 2; i<s; ++i) {
        premier._cards.push_back(all_cards[2*i]);
        second._cards.push_back(all_cards[2*i+1]);
    }
}

Card Player::operator[] (const unsigned& i) {
    return _cards[i];
}

bool Player::play(Player& premier, Player& second) {

    Card card1 = premier[Player::turn_number+Player::card_offset];
    Card card2 = second[Player::turn_number+Player::card_offset];

    // afficher les deux cartes jouées au tour courant
    std::cout << "Joueur 1 (" << premier._name << "): " << card1 << std::endl;
    std::cout << "Joueur 2 (" << second._name << "): " << card2 << std::endl;

    // mettre à jour les scores
    if(card1 < card2) {
        std::cout << "Joueur 2 remporte le pli" << std::endl;
        ++second._score;
    }
    else if (card2 < card1) {
        std::cout << "Joueur 1 remporte le pli" << std::endl;
        ++premier._score;
    }
    else {
        // Gestion des égalité (question bonus 6)

        unsigned new_offset=1;
        while (premier._cards.size() > (Player::turn_number+Player::card_offset+new_offset)) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // bonus
            Card card1 = premier[Player::turn_number+Player::card_offset+new_offset];
            Card card2 = second[Player::turn_number+Player::card_offset+new_offset];
            // afficher les deux cartes jouées au tour courant

                std::cout << "  Egalité (n°" << new_offset << ")" << std::endl;
                std::cout << "  Joueur 1 (" << premier._name << "): " << card1 << std::endl;
                std::cout << "  Joueur 2 (" << second._name << "): " << card2 << std::endl;

            // mettre à jour les scores
                if(card1 < card2) {
                    std::cout << "  Joueur 2 remporte l'égalité (" << new_offset+1 << " points)" <<std::endl;
                    second._score+=new_offset+1;
                    break;
                }
                else if (card2 < card1) {
                    std::cout << "  Joueur 1 remporte l'égalité (" << new_offset+1 << " points)" <<std::endl;
                    premier._score+=new_offset+1;
                    break;
                }
                else {
                    ++new_offset;
                    if (premier._cards.size() <= (Player::turn_number+Player::card_offset+new_offset)) {
                        std::cout << "  Plus assez de cartes pour départager l'égalité. Personne ne gagne de points" << std::endl;
                        return false;
                    }
                }
        }
        Player::card_offset+=new_offset;
    }
    ++Player::turn_number;

    return premier._cards.size() > Player::turn_number+Player::card_offset;
}

unsigned int Player::get_score() const {
    return _score;
}
