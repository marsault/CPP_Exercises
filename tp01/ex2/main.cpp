#include <iostream>
#include <vector>

void ajoute_double(std::vector<int>& v) {
    auto size = v.size();
    for (auto i = 0; i < size; i++)
    {
        v.push_back(v[i] * 2);
    }
}

void affiche(const std::vector<int>& v) {
    std::cout << "Le tableau contient les valeurs :";
    for (auto entier : v)
    {
        std::cout << " " << entier;
    }
    std::cout << std::endl;
}

int main() {
    auto entiers = std::vector<int> {};
    auto value   = 0;
    while (1)
    {
        std::cin >> value;
        if (std::cin.fail())
        {
            std::cout << "Ceci n'est pas un entier !" << std::endl;
            return 1;
        }
        if (value == 0)
        {
            break;
        }
        if (value < 0)
        {
            if (!entiers.empty())
                entiers.pop_back();
        }
        else
        {
            entiers.emplace_back(value);
        }
    }
    affiche(entiers);
    if (!entiers.empty())
        std::cout << "first: " << entiers.front() << "    last: " << entiers.back() << std::endl;
    ajoute_double(entiers);

    affiche(entiers);
    return 0;
}