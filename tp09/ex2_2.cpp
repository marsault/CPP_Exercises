#include <algorithm>
#include <deque>
#include <iostream>
#include <string>

struct Animal
{
    std::string name;
    std::string species;
};

std::ostream& operator<<(std::ostream& str, const Animal& animal)
{
    return str << animal.name << " (" << animal.species<< ")";
}

std::ostream& operator<<(std::ostream& str, const std::deque<Animal>& animals)
{
    str << "[";
    for (size_t idx = 0, end = animals.size(); idx < end; ++idx)
    {
        str << idx << ": "<< animals[idx];
        if (idx + 1 < end)
        {
            str << ", ";
        }
    }
    str << "]";
    return str;
}

std::ptrdiff_t get_position_of_first_with_species(const std::deque<Animal>& animals, const std::string& species)
{
    auto result = std::find_if(animals.begin(), animals.end(), [species](const Animal& animal) {return animal.species == species;});
    return animals.end() - result;
}

int main()
{
    std::deque<Animal> animals;
    animals.push_back({ "felix", "cat" });
    animals.push_back({ "medor", "dog" });
    animals.push_back({ "guss", "mouse" });
    animals.push_back({ "gipsy", "dog" });
    animals.push_back({ "chaussette", "cat" });
    animals.push_back({ "pelotte", "cat" });

    std::cout << animals << std::endl;

    std::cout << "First dog is at: " << get_position_of_first_with_species(animals, "dog") << std::endl;
    std::cout << "First poney is at: " << get_position_of_first_with_species(animals, "poney") << std::endl;
    std::cout << "First mouse is at: " << get_position_of_first_with_species(animals, "mouse") << std::endl;

    return 0;
}

