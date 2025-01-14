#include <iostream>

void ajoute_double(std::vector<int> v)
{
    for (auto n : v)
    {
        v.emplace_back(n * 2);
    }
}

int main()
{
    auto entiers = std::vector<int>{1, 3, 3, 7};

    std::cout << "Le tableau contient les valeurs :";
    for (int i = 0; i < entiers.size(); i++)
    {
        std::cout << " " << entiers[i];
    }
    std::cout << std::endl;

    ajoute_double(entiers);

    return 0;
}