#pragma once
#include "Entity.hpp" // Entity

// Classe Item regroupant les points communs de Trap et Potion, à savoir:
//  - la construction (placement aléatoire sur la grille)
//  - update (on ne fait rien)
// question C.4       
class Item : public Entity {
    public:
        Item(int width, int height) : Entity(random_value(1, width-1), random_value(1, height-1)) 
        {
            is_consumed = false; // question E.3
        }
        void update()                   override { }
        void consume() { is_consumed = true; } // question E.3

    protected:
        bool is_consumed; // question E.3
};
