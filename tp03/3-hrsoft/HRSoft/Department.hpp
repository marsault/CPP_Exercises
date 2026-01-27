#pragma once

#include "Employee.hpp"

#include <iostream>
#include <list>
#include <string>

class Department {
public:
  Department(const std::string &name) : _name{name} {}

  Employee &add_employee(const std::string &name, unsigned int salary,
                         Employee *manager) {
    auto &employee = _employees.emplace_back(name, salary);

    if (manager != nullptr)
      manager->add_subordinate(employee);

    return employee;
  }

  inline void print_employees(bool header = true) {
    if (header)
      std::cout << "List of employees in " << this->_name << std::endl;
    for (auto &employee : _employees)
      std::cout << "\t- " << employee << std::endl;
  }

  inline const std::string &name() { return _name; }

  inline void remove_subordinate(const Employee& employee) {
    for (auto& m : _employees)
      m.remove_subordinate(employee);
  }

  inline bool remove_employee(Employee &employee) {
    for (auto it = _employees.begin(); it != _employees.end(); ++it)
      if (&(*it) == &employee) {
        _employees.erase(it);
        return true;
      }
    return false;
  }

private:
  std::string _name;
  std::list<Employee> _employees;
};
