#pragma once

#include <list>
#include <string>

#include "Department.hpp"

class HRSoftSystem {
public:
  Department &add_department(const std::string &name) {
    return _departments.emplace_back(name);
  }

  inline void print_all_employees() {
    std::cout << "List of all employees:" << std::endl;
    for (auto &d : _departments) {
      d.print_employees(false);
    }
  }

  inline void print_all_departments() {

    std::cout << "List of all departments:" << std::endl;
    for (auto &d : _departments) {
      std::cout << "\t- " << d.name() << std::endl;
    }
  }

  inline bool remove_employee(Employee &employee) {
    // On supprime l'employée de toutes les listes de subordonnée
    for (auto &d : _departments)
      d.remove_subordinate(employee);
    // On supprime ensuite l'employé lui-même.
    for (auto &d : _departments) {
      if (d.remove_employee(employee))
        return true;
    }
    return false;
  }

private:
  std::list<Department> _departments;
};
