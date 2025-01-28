#include "HRSoft/HRSoftSystem.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::stringstream get_next_line()
{
    auto line = std::string {};
    std::getline(std::cin, line);
    return std::stringstream { line };
}

std::string parse_string(std::istream& stream)
{
    auto name = std::string {};
    stream >> name;
    return name;
}

unsigned int parse_value(std::istream& stream)
{
    auto salary = 0u;
    stream >> salary;
    return salary;
}

int main()
{
    std::cout << "Welcome in HRSoft!" << std::endl;

    auto system = HRSoftSystem {};
    auto command = ' ';
    
    while (command != 'q')
    {
        std::cout << "What do you want to do? (tap 'h' for help)" << std::endl;

        auto next_line = get_next_line();
        next_line >> command;

        switch (command)
        {
            case 'd':
                //std::cout << "Not implemented yet" << std::endl;
                system.add_department(parse_string(next_line));                
                break;
 
            case 'l':
                //std::cout << "Not implemented yet" << std::endl;
                system.print_all_departments();
                break;

            case 'e':
                std::cout << "Not implemented yet" << std::endl;
                // if (auto* dpt = system.find_department(parse_string(next_line)))
                // {
                //     auto name = parse_string(next_line);
                //     auto salary = parse_value(next_line);
                //     auto* manager = system.find_employee(parse_string(next_line));
                //     dpt->add_employee(name, salary, manager);
                // }
                break;

            case 'k':
                std::cout << "Not implemented yet" << std::endl;
                // system.print_all_employees();
                break;

            case 'f':
                std::cout << "Not implemented yet" << std::endl;
                // if (auto* employee = system.find_employee(parse_string(next_line)))
                // {
                //     system.remove_employee(*employee);
                // }
                break;

            case 'n':
                std::cout << "Not implemented yet" << std::endl;
                // ...
                break;

            case 'm':
                std::cout << "Not implemented yet" << std::endl;
                // ...
                break;

            case 't':
                std::cout << "Not implemented yet" << std::endl;
                // ...
                break;

            case 's':
                std::cout << "Not implemented yet" << std::endl;
                // ...
                break;

            case 'h':
                // commande d'aide
                std::cout << "Available commands:" << std::endl;
                std::cout 
                    << "    " << "d DEP                : adds a department named DEP " << std::endl
                    << "    " << "l                    : lists all departments " << std::endl
                    << "    " << "e NAME SALARY MANAGER: adds a new employee named NAME with their SALARY and MANAGER" << std::endl
                    << "    " << "k                    : lists all employees" << std::endl
                    << "    " << "f NAME               : removes employee NAME" << std::endl
                    << "    " << "n DEP                : lists all employees in department DEP" << std::endl
                    << "    " << "m                    : lists all managers" << std::endl
                    << "    " << "m NAME               : lists all subordinates of manager NAME" << std::endl
                    << "    " << "t NAME TARGET        : moves employee NAME to department TARGET" << std::endl
                    << "    " << "r NAME AMOUNT        : raises employee NAME's by AMOUNT" << std::endl
                    << "    " << "s                    : prints the sum of all salaries by department" << std::endl;
                    break;

            default:
                std::cout << "Unknown command " << command << std::endl;
                break;
        }
    }

    return 0;
}
