#include "Entity.hpp" // Entity

// question C.3
class Potion : public Entity {
    public:
        Potion(int width, int height) : Entity(random_value(1, width-1), random_value(1, height-1)) {}
        
        char get_representation() const override { return '$'; }  
        void update()                   override { }

};
