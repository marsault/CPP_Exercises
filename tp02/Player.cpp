#include "Player.hpp"

#include "Card.hpp"

#include <algorithm>
#include <random>
#include <vector>

Player::Player(std::string name)
    : _name { name }
    , _score { 0u } {};

unsigned int Player::turn_number = 0u;

void Player::deal_all_cards(Player& p1, Player& p2) {
    std::vector<Card> all_cards;
    for (unsigned int i = 7; i < 15; i++)
    {
        for (unsigned int j = 1; j < 5; j++)
        {
            all_cards.emplace_back(i, j);
        }
    }

    std::random_device rd;
    std::shuffle(all_cards.begin(), all_cards.end(), std::default_random_engine(rd()));
    auto milieu = all_cards.size() / 2;
    p1._cards.assign(all_cards.begin(), all_cards.begin() + milieu);
    p2._cards.assign(all_cards.begin() + milieu, all_cards.end());
}

Card Player::operator[](unsigned int index) const {
    if (index < _cards.size())
        return _cards[index];
    std::cerr << "Problème d'index !!!" << std::endl;
    exit(EXIT_FAILURE);
}

unsigned int Player::get_score() const {
    return _score;
}
std::string Player::get_name() const {
    return _name;
}

bool Player::play(Player& p1, Player& p2) {
    std::cout << "Turn Number: " << turn_number + 1 << std::endl;
    std::cout << "Carte de " << p1._name << ": " << p1._cards[turn_number] << std::endl;
    std::cout << "Carte de " << p2._name << ": " << p2._cards[turn_number] << std::endl;
    if (!(p1._cards[turn_number] == p2._cards[turn_number]))
    {
        if (p1._cards[turn_number] < p2._cards[turn_number])
        {
            std::cout << p2._name << " a gagné 1 point." << std::endl;
            p2._score++;
        }
        else
        {
            std::cout << p1._name << " a gagné 1 point." << std::endl;
            p1._score++;
        }
    }
    else {
        turn_number++;
        equality(p1, p2, 1);
    }
    turn_number++;
    return turn_number >= 15;
}

void Player::equality(Player& p1, Player& p2, int point_to_win) {
    if (turn_number >= 15) {
        return;
    }
    std::cout << "C'est une égalité, on rejoue !!" << std::endl;
    std::cout << "Carte de " << p1._name << ": " << p1._cards[turn_number] << std::endl;
    std::cout << "Carte de " << p2._name << ": " << p2._cards[turn_number] << std::endl;
    if (!(p1._cards[turn_number] == p2._cards[turn_number]))
    {
        if (p1._cards[turn_number] < p2._cards[turn_number])
        {
            std::cout << p2._name << " a gagné " << point_to_win + 1 << " points." << std::endl;
            p2._score += point_to_win + 1;
        }
        else
        {
            std::cout << p1._name << " a gagné " << point_to_win + 1 << " points." << std::endl;
            p1._score += point_to_win + 1;
        }
    }
    else {
        turn_number++;
        equality(p1, p2, ++point_to_win);
    }
}