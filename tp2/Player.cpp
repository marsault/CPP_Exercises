#include "Player.hpp"

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