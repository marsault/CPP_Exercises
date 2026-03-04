#pragma once

#include <cctype>
#include <iostream>

#include "Entity.hpp" // Entity
#include "Trap.hpp"
#include "Potion.hpp"
#include "Logger.hpp"

// question B.1: la classe vide suffit
class Character: public Entity {
    public:
        Character(int x, int y) : Entity(x, y) // question B.2
        {
            // question B.5
            logger << "Character " << _name << " was created at (" << x << ',' << y << ")" << std::endl;
            _lives_left = 2; // question D.2
        }
        char get_representation() const override
        {
            // return 'O'; // question B.3
            // return _name; // question B.4
            // question D.2:
            switch (_lives_left)
            {
                case  2: return _name;
                case  1: return std::tolower(_name);
                default: return ' ';
            }

        }

        // question D.2
        void interact_with(Entity& entity) override
        {
            auto* trap = dynamic_cast<Trap*>(&entity);
            if (trap != nullptr)
            {
                // entity est bien une instance de Trap
                --_lives_left;
                // question D.3
                logger << "Character " << _name << " has walked into a trap" << std::endl;
                trap->consume(); // question E.3
            }
            else
            {   // question D.5
                auto* potion = dynamic_cast<Potion*>(&entity);
                if (potion != nullptr && _lives_left < 2)
                {
                    // entity est bien une instance de Potion
                    ++_lives_left;
                    logger << "Character " << _name << " has drunk a potion" << std::endl;
                    // question E.3
                    potion->consume();
                }

            }
        }

        // question E.1
        bool should_destroy() const override { return not _lives_left; }

        // question E.4
        ~Character() override
        {
            logger << "Character " << _name << " has died at position (" << get_x() << ", " << get_y() << ")" << std::endl;
        }

    private:
        // question B.4
        static inline char next_name = 'A';
        char _name = next_name++;
        // question D.2
        int _lives_left;
};
