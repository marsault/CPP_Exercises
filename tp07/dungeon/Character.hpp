#pragma once

#include "Entity.hpp"
#include "Trap.hpp"
#include "Potion.hpp"
#include "Logger.hpp"

class Character : public Entity
{
private:
    char who_i_am = 'O';
public:
    Character(int x, int y):Entity {x, y} {
    }

    ~Character() override{
        logger << "A character died at position (" << get_x() << ", " << get_y() << ")" << std::endl;
    }

    char get_representation() const override { return who_i_am; }

    void interact_with (Entity& entity) override {
        auto* trap = dynamic_cast<Trap*>(&entity);
        if (trap != nullptr)
        {
            trap->destroy();
            switch (who_i_am)
            {
            case 'O':
                who_i_am = 'o';
                break;
            case 'o':
                destroy();
                break;
            default:
                break;
            }
            return;
        }

        auto* potion = dynamic_cast<Potion*>(&entity);
        if (potion != nullptr)
        {
            switch (who_i_am)
            {
            case 'o':
                potion->destroy();
                who_i_am = 'O';
                break;
            default:
                break;
            }
        }
    }
};
