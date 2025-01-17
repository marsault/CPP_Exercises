#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    std::cout << "Entre ton nom: ";

    //char name[20] = "";
    std::string name;
    std::cin >> std::setw(20) >> name;
    std::cout << name << std::endl;
    //std::cout << "Bonjour Palluche La Falluche !" << std::endl;

    return 0;
}