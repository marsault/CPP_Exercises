#include <vector>
#include <iostream>

void ajoute_double(std::vector<int>& entiers) {
    std::vector<int> tmp = entiers;
    for(auto n: tmp) {
        entiers.emplace_back(n * 2);
    }
}

void affiche(std::vector<int>& entiers) {
    for (auto n: entiers) {
        std::cout << " " << n;
    }
    std::cout << std::endl;
}

std::vector<int> read_values() {
    auto vec = std::vector<int>{};
    while(true) {
        int v;
        std::cin >> v;
        if(std::cin.fail()) {
            std::cerr << "Ceci n'est pas un entier !" << std::endl;
            vec.clear();
            break;
        }
        if(v == 0) {
            break;
        }
        if(v < 0) {
            vec.pop_back();
        }
        else {
            vec.emplace_back(v);
        }
    }
    return vec;
}

int main()
{
    //std::vector<int> entiers = {1, 3, 3, 7};
    auto entiers = read_values();

    std::cout << "Le tableau contient les valeurs :" << std::endl;
    /*for (int i = 0; i < entiers.size(); i++) {
        std::cout << " " <<  entiers[i];
    }*/
   std::cout << "First element: " << entiers.front() << std::endl;
   std::cout << "Last element: " << entiers.back() << std::endl;
   for(auto i: entiers) {
    std::cout << " " <<  i;// contenu du tableau en une boucle for-each
   }
    std::cout << std::endl;

    /*for (auto n: entiers) {
        entiers.emplace_back(n * 2);
    }*/

   ajoute_double(entiers);

    affiche(entiers);

    return 0;
}
