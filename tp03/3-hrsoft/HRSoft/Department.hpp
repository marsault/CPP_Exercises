#pragma once

#include "Employee.hpp"

#include <iostream>
#include <list>
#include <string>

class Department
{
public:
    Department(const std::string& name)
        : _name { name } {}

    Employee& add_employee(const std::string& name, unsigned int salary, Employee* manager) {
        auto& employee = _employees.emplace_back(name, salary);

        if (manager != nullptr)
        {
            manager->add_subordinate(employee);
        }

        return employee;
    }

    void print_employees() const {
        std::cout << "Employees of " << _name << " department:" << std::endl;
        for (const auto& employee : _employees)
        {
            std::cout << "  - " << employee << std::endl;
        }
    }

    const std::string& get_name() const { return _name; }

    void remove_employee(Employee& employee) {
        for (auto& _employee : _employees)
        {
            _employee.remove_subordinate(employee);
        }
        _employees.remove(employee);
    }

    const std::list<Employee>& get_employees() const { return _employees; }

    Employee* find_employee(const std::string& name) {
        for (auto& employee : _employees)
        {
            if (employee.get_name() == name)
            {
                return &employee;
            }
        }
        return nullptr;
    }

private:
    std::string         _name;
    std::list<Employee> _employees;
};
