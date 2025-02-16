#pragma once

#include "Department.hpp"
#include "Employee.hpp"

#include <list>
#include <string>

class HRSoftSystem
{
public:
    Department& add_department(const std::string& name) { return _departments.emplace_back(name); }

    void print_all_departments() const {
        std::cout << "Departments:" << std::endl;
        for (const auto& department : _departments)
        {
            std::cout << "  - " << department.get_name() << std::endl;
        }
    }

    void print_all_employees() const {
        std::cout << "Employees:" << std::endl;
        for (const auto& department : _departments)
        {
            department.print_employees();
        }
    }

    void remove_employee(Employee& employee) {
        for (auto& department : _departments)
        {
            department.remove_employee(employee);
        }
    }

    void add_department(std::string& departement_name) {
        for (auto& department : _departments)
        {
            if (department.get_name() == departement_name)
            {
                return;
            }
        }
        _departments.emplace_back(departement_name);
    }

    Department* find_department(const std::string& name) {
        for (auto& department : _departments)
        {
            if (department.get_name() == name)
            {
                return &department;
            }
        }
        return nullptr;
    }

    Employee* find_employee(const std::string& name) {
        for (auto& department : _departments)
        {
            if (auto* employee = department.find_employee(name))
            {
                return employee;
            }
        }
        return nullptr;
    }

    void list_managers() const {
        std::cout << "Managers:" << std::endl;
        for (const auto& department : _departments)
        {
            for (const auto& employee : department.get_employees())
            {
                if (!employee.is_manager())
                {
                    std::cout << "  - " << employee << std::endl;
                }
            }
        }
    }

private:
    std::list<Department> _departments;
};
