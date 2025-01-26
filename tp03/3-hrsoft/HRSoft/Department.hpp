#pragma once

#include "Employee.hpp"

#include <iostream> // cout
#include <list>
#include <string>

class Department
{
public:
    Department(const std::string& name)
        : _name { name }
    {}

    Employee& add_employee(const std::string& name, unsigned int salary, Employee* manager)
    {
        auto& employee = _employees.emplace_back(name, salary);

        if (manager != nullptr)
        {
            manager->add_subordinate(employee);
        }

        return employee;
    }

    // Exercice 3.2
    void print_employees() const 
    {
        for(const auto& emp: _employees)
        {
            std::cout << emp << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream&, const Department&);


private:
    std::string _name;
    std::list<Employee> _employees;
};

// Exercice 3.2: ajout d'un opérateur << sur le modèle de celui fourni pour Employee; 
// ne pas oublier de le déclarer "friend" dans Department pour lui donner accès aux champs privés requis
inline std::ostream& operator<<(std::ostream& stream, const Department& department)
{
    return stream << department._name ;
}
