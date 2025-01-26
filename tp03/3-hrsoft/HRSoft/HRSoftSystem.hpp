#pragma once

#include "Department.hpp"

#include <list>
#include <string>

class HRSoftSystem
{
public:
    Department& add_department(const std::string& name)
    {
        return _departments.emplace_back(name);
    }

    // Exercice 3.2
    void print_all_departments() const 
    {
        std::cout << "Departments:" << std::endl;
        for(const auto& dep: _departments)
        {
            std::cout << "    - " << dep << std::endl;
        }
    }

    void print_all_employees() const 
    {
        std::cout << "All employees:" << std::endl;
        for(const auto& dep: _departments)
        {
            dep.print_employees();
        }
    }


private:
    std::list<Department> _departments;
};
