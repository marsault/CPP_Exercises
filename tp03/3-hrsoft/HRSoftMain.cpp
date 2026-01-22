#include <iostream>
#include <sstream>
#include <string>

#include "HRSoft/HRSoftSystem.hpp"

std::stringstream get_next_line()
{
  auto line = std::string{};
  std::getline(std::cin, line);
  return std::stringstream{line};
}

std::string parse_string(std::istream& stream)
{
  auto name = std::string{};
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

  auto system = HRSoftSystem{};
  auto command = ' ';

  while (command != 'q') {
    std::cout << "What do you want to do? (tap 'h' for help)" << std::endl;

        switch (command)
        {
            case 'd': // adds a department named DEP
                system.add_department(parse_string(next_line));                
                break;
 
            case 'l':  // lists all departments
                system.print_all_departments();
                break;

            case 'e': // adds a new employee named NAME with their SALARY [and MANAGER] to a given DEP
                if (auto* dpt = system.find_department(parse_string(next_line)))
                {
                    auto name = parse_string(next_line);
                    auto salary = parse_value(next_line);
                    auto* manager = system.find_employee(parse_string(next_line));
                    dpt->add_employee(name, salary, manager);
                }
                else
                {
                    std::cout << "Error: selected department does not exist" << std::endl;
                }
                break;

            case 'k':  // lists all employees
                system.print_all_employees();
                break;

            case 'f':
                if (auto* employee = system.find_employee(parse_string(next_line)))
                {
                    system.remove_employee(*employee);
                }
                break;

            case 't':
                if (auto* employee = system.find_employee(parse_string(next_line)))
                {
                    system.move_employee(parse_string(next_line), parse_string(next_line));
                }
                break;

    case 'm':
      std::cout << "Not implemented yet" << std::endl;
      // ...
      break;

            case 'h':
                // commande d'aide
                std::cout << "Available commands:" << std::endl;
                std::cout 
                    << "    " << "d DEP                     : adds a department named DEP " << std::endl
                    << "    " << "l                         : lists all departments " << std::endl
                    << "    " << "e DEP NAME SALARY MANAGER : adds a new employee named NAME with their SALARY and MANAGER to department DEP" << std::endl
                    << "    " << "k                         : lists all employees" << std::endl
                    << "    " << "f NAME                    : removes employee NAME" << std::endl
                    << "    " << "n DEP                     : lists all employees in department DEP" << std::endl
                    << "    " << "m                         : lists all managers" << std::endl
                    << "    " << "m NAME                    : lists all subordinates of manager NAME" << std::endl
                    << "    " << "t NAME TARGET             : moves employee NAME to department TARGET" << std::endl
                    << "    " << "r NAME AMOUNT             : raises employee NAME's by AMOUNT" << std::endl
                    << "    " << "s                         : prints the sum of all salaries by department" << std::endl;
                    break;

            case 'q':
                std::cout << "Exiting... " << std::endl;
                break;

            default:
                std::cout << "Unknown command " << command << std::endl;
                break;
        }
    }
  }

  return 0;
}
