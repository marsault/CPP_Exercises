#include <vector> // <- Question 2
#include <iostream>

void ajoute_double(std::vector<int> &v)
{
    auto v_double = std::vector<int>{};
    for (auto n : v)
        v_double.emplace_back(n * 2);
    for (auto n : v_double)
        v.emplace_back(n);
}

void affiche(const std::vector<int> &v)
{
    std::cout << "Le tableau contient les valeurs :";
    for (auto i : v)
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> entiers = {};

    bool done = false;

    while (!done)
    {
        int last_input = 0;
        std::cin >> last_input;
        if (std::cin.fail())
        {
            std::cout << "Ceci n'est pas entier!" << std::endl;
            exit(-1);
        }

        done = (last_input == 0);
        if (last_input > 0)
            entiers.emplace_back(last_input);
        if (last_input == -1 && !entiers.empty())
            entiers.pop_back();
    }

    affiche(entiers);
    ajoute_double(entiers);
    affiche(entiers);

    return 0;
}
