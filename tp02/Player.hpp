#include "Card.hpp"

#include <iostream>
#include <string>
#include <vector>
#pragma once

class Player
{
public:
    static unsigned int turn_number;
    Player(std::string name);
    static void  deal_all_cards(Player& p1, Player& p2);
    Card         operator[](unsigned int index) const;
    static bool  play(Player& p1, Player& p2);
    unsigned int get_score() const;
    std::string  get_name() const;

private:
    std::string       _name;
    std::vector<Card> _cards;
    unsigned int      _score;
    static void equality(Player& p1, Player& p2, int point_to_win);
};