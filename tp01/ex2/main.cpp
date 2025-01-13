#include <vector>
#include <iostream>

int main()
{
    std::vector<int> entiers = {1, 3, 3, 7};

    std::cout << "Le tableau contient les valeurs :";
    for (int i = 0; i < entiers.size(); i++) {
        std::cout << " " <<  entiers[i];
    }
    std::cout << std::endl;

    for (auto n: entiers) {
        entiers.emplace_back(n * 2);
    }

    for (auto n: entiers) {
        std::cout << " " << n;
    }
    std::cout << std::endl;

    return 0;
}
