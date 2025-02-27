#include "Entity.hpp" // Entity

// la définition suivante vide suffit pour la question B.1
class Character: public Entity {
    public:
    Character(int x, int y) : Entity(x, y) {} // question B.2
    char get_representation() const override { return 'O'; }  // question B.3

};
