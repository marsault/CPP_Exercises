#pragma once
// question C.1 (version pré-refactorisation)
/*
#include "Entity.hpp" // Entity

class Trap : public Entity {
    public:
        Trap(int width, int height) : Entity(random_value(1, width-1), random_value(1, height-1)) {}
        
        char get_representation() const override { return 'X'; }  
        void update()                   override { } // question C.2

};
*/

// question C.4 (version post-refactorisation)
#include "Item.hpp"
#include "Character.hpp"

class Trap : public Item {
    public:  
        Trap(int width, int height) : Item(width, height) { }
        char get_representation() const override { return 'X'; }  


        // question E.1
        bool should_destroy() const override { return is_consumed; }

};
