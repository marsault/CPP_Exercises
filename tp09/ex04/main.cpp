#include <set>
#include <tuple> // std::tie
#include <iostream>

// question A.1
struct Point3d 
{
    int x, y, z;
    Point3d(int a, int b, int c) : x(a), y(b), z(c) {};
    bool operator<(const Point3d& autre) const 
    {
        // on se contente d'une comparaison lexicographique
        return std::tie(x, y, z) < std::tie(autre.x, autre.y, autre.z);
    }
};

// question B.1
class Point3dCompare
{
    public:
        bool operator()(const Point3d& premier, const Point3d& second) const 
        {
            // on se contente d'une comparaison lexicographique
            return std::tie(premier.x, premier.y, premier.z) < std::tie(second.x, second.y, second.z);
        }
};

// question B.3 (pour les tests)
void afficher_contenu(const std::set<
    Point3d
    // , Point3dCompare // question B.2; à supprimer après la question C.2
    >& data) 
{
    for (auto& triplet : data) 
        std::cout << "(" << triplet.x << ", " << triplet.y << ", " << triplet.z << ")" << std::endl;
}

int main()
{   
    // question A.2
    std::set<
        Point3d
        //,Point3dCompare // question B.2; à supprimer après la question C.2
    > coords;
    // question A.3
    /* jusqu'ici, tout va bien car on n'a encore rien tenté d'insérer dans la structure; mais 
       dès qu'on essaie de le faire comme ci-dessous, le set doit effectuer des comparaisons, qu'il
       ne sait pas comment réaliser puisqu'on ne le lui a pas expliqué, d'où l'erreur de compilation
    */
   coords.insert(Point3d(1, 2, 3)); // échec à la A.3, mais fonctionne après la B.2
   coords.insert(Point3d(4, 5, 6));
   // question B.3
   std::cout << "Contenu de la structure après " << coords.size() << " insertions:" << std::endl;
   afficher_contenu(coords);
   std::cout << "Contenu de la structure après suppressions du \"premier\" élément:" << std::endl;
   coords.erase(coords.begin());
   afficher_contenu(coords);    
}