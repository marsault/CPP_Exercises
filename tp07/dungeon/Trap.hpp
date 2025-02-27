#include "Entity.hpp" // Entity

// question C.1 (version pré-refactorisation)
class Trap : public Entity {
    public:
        Trap(int width, int height) : Entity(random_value(1, width-1), random_value(1, height-1)) {}
        
        char get_representation() const override { return 'X'; }  
        void update()                   override { } // question C.2

};
