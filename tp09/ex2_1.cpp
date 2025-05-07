#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Animal
{
    std::string name;
    std::string species;
};

std::ostream& operator<<(std::ostream& str, const Animal& animal)
{
    return str << animal.name << " (" << animal.species<< ")";
}

std::ostream& operator<<(std::ostream& str, const std::vector<Animal>& animals)
{
    str << "[-";
    for (const auto& a: animals)
    {
        str << " " <<  a << " -";
    }
    str << "]";
    return str;
}

void remove_cats(std::vector<Animal>& animals)
{
    auto n = std::remove_if(animals.begin(), animals.end(), [](Animal& animal) {return animal.species == "cat";});
    animals.erase(n, animals.end());
}

int main()
{
    std::vector<Animal> animals;
    animals.push_back({ "felix", "cat" });
    animals.push_back({ "medor", "dog" });
    animals.push_back({ "guss", "mouse" });
    animals.push_back({ "gipsy", "dog" });
    animals.push_back({ "chaussette", "cat" });
    animals.push_back({ "pelotte", "cat" });

    std::cout << animals << std::endl;

    remove_cats(animals);
    std::cout << animals << std::endl;

    return 0;
}

