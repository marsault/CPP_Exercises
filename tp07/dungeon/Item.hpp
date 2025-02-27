#pragma once
#include "Entity.hpp" // Entity

// Classe Item regroupant les points communs de Trap et Potion, à savoir:
//  - la construction (placement aléatoire sur la grille)
//  - update (on ne fait rien)
// question C.4       
class Item : public Entity {
    public:
        Item(int width, int height) : Entity(random_value(1, width-1), random_value(1, height-1)) {}
        void update()                   override { }
};
