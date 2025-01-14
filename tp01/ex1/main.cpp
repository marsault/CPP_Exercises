#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    std::cout << "Entre ton nom: ";

    auto name = std::string{};
    std::cin >> name;
    std::cout << "Bonjour " << name << "!" << std::endl;

    return 0;
}
