#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "Card.hpp"

class Player {
    public:
        Player(const std::string& _name);
        void print() const;
        static void deal_all_cards(Player& p1, Player& p2);

        const Card& operator[](size_t index) const;

        static bool play(Player& p1, Player& p2);

        unsigned int get_score() const;

        const std::vector<Card>& get_cards() const;
        

    private:
        std::string _name;
        std::vector<Card> _cards;
        unsigned int _score = 0u;

        static unsigned int turn_number;
};