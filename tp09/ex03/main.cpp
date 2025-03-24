#include <iostream>
#include <unordered_map>

// question A.1
struct Point2d 
{
    int x, y;
    // question B.3: on rajoute un constructeur pour pouvoir faire des tests plus ergonomiquement
    Point2d(int a, int b) : x(a), y(b) {};
    // question C.1: attention, l'opérateur DOIT être const (cf https://en.cppreference.com/w/cpp/utility/functional/equal_to)
    bool operator==(const Point2d& autre) const { 
        return (x * x + x + 2 * x * y + 3 * y + y * y) 
        == (autre.x * autre.x + autre.x + 2 * autre.x * autre.y + 3 * autre.y + autre.y * autre.y);
    };
};

// question A.2
enum class Content {Empty, Red, Yellow};

// question C.2
namespace std {   // il faut se placer dans le bon namespace
    template <>
    struct hash<Point2d>
    {
        size_t operator()(const Point2d& point) const 
        {
            // Cantor pairing function, voir
            // https://en.wikipedia.org/wiki/Pairing_function
            auto x = point.x, y = point.y;
            return (x * x + x + 2 * x * y + 3 * y + y * y) / 2;
        }
    };    
}
    
// question B.1
class Point2dHash 
{
    public:
        // attention à la syntaxe: c'est bien operator() pour désigner
        // l'opérateur (), suivi de (paramètres)
        std::size_t operator()(const Point2d& point) const 
        {
            // Cantor pairing function, voir
            // https://en.wikipedia.org/wiki/Pairing_function
            const auto x = point.x, y = point.y;
            return (x * x + x + 2 * x * y + 3 * y + y * y) / 2;
        };
};

// question B.2
class Point2dEqual 
{
    public:
        bool operator()(const Point2d& premier, const Point2d& second) const 
        {
            // premier == second <=> hash(premier) == hash(second)
            auto comparateur = Point2dHash();
            return comparateur(premier) == comparateur(second);
        };
};
    
    
// question B.3 (pour les tests)
void afficher_contenu(const std::unordered_map<Point2d, Content
//    , Point2dHash  // plus nécessaire après la question C.2
//    , Point2dEqual  // plus besoin après question C.1
    >& grid) 
{
        for (const std::pair<Point2d, Content>& paire : grid) {
            std::cout << "(" << paire.first.x << ", " << paire.first.y << "): " ;
            switch(paire.second) {
                case Content::Empty:    std::cout << "Empty";               break;
                case Content::Red:      std::cout << "Red";                 break;
                case Content::Yellow:   std::cout << "Yellow";              break;
                default:                std::cout << "[couleur inconnue]";
            }
            std::cout << std::endl;
        }
    }

// question A.3
int main() 
{
    /* question A.3: ceci ne compile pas quand on n'a fait que la question A, car unordered_map
    ne sait pas comment "hasher" les instances de Point2d */
    // std::unordered_map<
    //     Point2d // type des clés
    //     ,Content // type des valeurs
    // > grid;
    // question B.3: on explique maintenant à la map comment hasher les Point2d
    std::unordered_map<
        Point2d // type des clés
        ,Content // type des valeurs
        //,Point2dHash // technique de hashage // plus nécessaire après la question C.2
        // ,Point2dEqual // comparateur // plus nécessaire après la question C.1
    > grid;

    // plus de problèmes de compilation après la question B.3, faisons quelques tests
    // ajout de données
    grid[Point2d(0, 0)] = Content::Empty;
    grid[Point2d(0, 1)] = Content::Red;
    grid[Point2d(1, 1)] = Content::Yellow;

    std::cout << "Voici le contenu de notre map:" << std::endl;
    afficher_contenu(grid);
    std::cout << "Supprimons le \"premier\" élément; notre map devient:" << std::endl;
    grid.erase(grid.begin());
    afficher_contenu(grid);

    return 0;
}
