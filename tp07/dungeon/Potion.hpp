// question C.3 (version pré-refactorisation)
/*
#include "Entity.hpp" // Entity

class Potion : public Entity {
    public:
        Potion(int width, int height) : Entity(random_value(1, width-1), random_value(1, height-1)) {}
        
        char get_representation() const override { return '$'; }  
        void update()                   override { }

};
*/

// question C.4 (version post-refactorisation)
#include "Item.hpp"

class Potion : public Item {
    public:        
        Potion(int width, int height) : Item(width, height) {}
        char get_representation() const override { return '$'; }  
};
