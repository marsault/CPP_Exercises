#include "Player.hpp"

unsigned int Player::turn_number = 0u;

Player::Player(const std::string& name)
    : _name {name}
    {}

void Player::print() const {
    std::cout << "Player: " << _name << std::endl;
}

void Player::deal_all_cards(Player& p1, Player& p2) {
    auto all_cards = std::vector<Card>{};
    const std::vector<std::string> colors = {"Pique", "Carreau", "Coeur", "Trèfle"};
    for(auto i = 1; i <= 13; ++i) {
        for(const auto& color: colors) {
            all_cards.emplace_back(i, color);
        }
    }
    std::random_device rd;
    std::shuffle(all_cards.begin(), all_cards.end(), std::default_random_engine(rd()));

    auto half = all_cards.size() / 2;
    p1._cards.assign(all_cards.begin(), all_cards.begin() + half);
    p2._cards.assign(all_cards.begin() + half, all_cards.end());
}

const Card& Player::operator[](size_t index) const {
    if(index >= _cards.size()) {
        std::cerr << "Index out of bounds" << std::endl;
    }
    return _cards[index];
}

const std::vector<Card>& Player::get_cards() const {
    return _cards;
}

unsigned int Player::get_score() const {
    return _score;
}

bool Player::play(Player& p1, Player& p2) {
    if(turn_number >= p1._cards.size() || turn_number >= p2._cards.size()) {
        return true;
    }
    std::cout << "Tour " << turn_number + 1 << std::endl;
    std::cout << p1._name << " joue ";
    p1[turn_number].print();
    std::cout << p2._name << " joue ";
    p2[turn_number].print();

    if (p2[turn_number] < p1[turn_number]) {
        ++p1._score;
    }
    if (p1[turn_number] < p2[turn_number]) {
        ++p2._score;
    } 

    turn_number++;
    return false;
}