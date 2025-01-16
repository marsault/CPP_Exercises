#include <vector> // <- Question 2
#include <iostream>

/* Solutions 1 and 2 does a full unnecessary copy */

void ajoute_double(std::vector<int> &v)
{
    auto v_double = std::vector<int>{};
    for (auto n : v)
        v_double.emplace_back(n * 2);
    for (auto n : v_double)
        v.emplace_back(n);
}

void ajoute_double2(std::vector<int> &v)
{
    auto temp = std::vector<int>{v};
    for (auto n : temp)
        v.emplace_back(n * 2);
}

/* Solution 3 has no copy, but depending on the implementation of std::vector, it might lead to multiple move of v in memory */

void ajoute_double3(std::vector<int> &v)
{
    auto size = v.size();
    for (size_t i = 0; i < size; ++i)
        v.emplace_back(v[i] * 2);
}

/* Function below is wrong: infinite loop. */
void wrong_ajoute_double(std::vector<int> &v)
{
    for (size_t i = 0; i < v.size(); ++i)
        v.emplace_back(v[i] * 2);
}

/* Solution 4 ensures that there is at most one move of v. */
void ajoute_double4(std::vector<int> &v)
{
    auto size = v.size();
    v.reserve(2 * size);
    for (size_t i = 0; i < size; ++i)
        v.emplace_back(v[i] * 2);
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
    std::vector<int> entiers = {1, 3, 3, 7};

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
