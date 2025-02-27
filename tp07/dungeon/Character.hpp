#pragma once
#include "Entity.hpp" // Entity
#include "Trap.hpp"
#include "Potion.hpp"

// question B.1: la classe vide suffit
class Character: public Entity {
    public:
        Character(int x, int y) : Entity(x, y) // question B.2
        {
            _lives_left = 2; // question D.2
        } 
        char get_representation() const override 
        { 
            // return 'O'; // question B.3
            // question D.2:
            switch (_lives_left)
            {
                case  2: return 'O'; 
                case  1: return 'o'; 
                default: return ' ';
            }
            
        }  
        
        // question D.2
        void interact_with(Entity& entity) override 
        {
            const auto* trap = dynamic_cast<Trap*>(&entity);
            if (trap != nullptr)
            {
                // entity est bien une instance de Trap
                --_lives_left;
            }
            else 
            {   // question D.4
                const auto* potion = dynamic_cast<Potion*>(&entity);
                if (potion != nullptr)
                {
                    // entity est bien une instance de Potion
                    ++_lives_left;
                }
    
            }
        }
        
        private:
            int _lives_left; // question D.2
};
