#include <string>
#include <vector>
#include "Card.hpp"

class Player {
    private:
        // question 1
        std::string _name;
        std::vector<Card> _cards;
        unsigned _score;
        inline static unsigned turn_number = 0;

    public:
        Player(const std::string&);
        ~Player();

        static void deal_all_cards(Player&, Player&);
        Card operator[] (const unsigned&);
        static bool play(Player&, Player&);
        unsigned get_score() const;
};


