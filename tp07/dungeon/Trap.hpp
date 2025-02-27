#include "Entity.hpp" // Entity

// question C.1
class Trap : public Entity {
    public:
        Trap(int width, int height) : Entity(random_value(0, width), random_value(0, height)) {}
        char get_representation() const override { return 'X'; }  

};
