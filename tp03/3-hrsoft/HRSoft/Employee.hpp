#pragma once

#include <iostream>
#include <list>
#include <ostream>
#include <string>

class Employee {
public:
  Employee(const std::string &name, unsigned int salary)
      : _name{name}, _salary{salary} {}

  void add_subordinate(Employee &employee) {
    _subordinates.emplace_back(&employee);
  }

  friend std::ostream &operator<<(std::ostream &, const Employee &);

  inline void print_subordinates(bool header = true) {
    if (header)
      std::cout << "List of " << _name << " subordinates" << std::endl;
    for (auto employee : _subordinates)
      std::cout << "\t- " << *employee << std::endl;
  }
  
  inline void remove_subordinate(const Employee& employee) {
    for (auto it = _subordinates.begin(); it != _subordinates.end(); ++it)
      if (*it == &employee) {
        _subordinates.erase(it);
        break;
      }
  }

private:
  std::string _name;
  unsigned int _salary = 0;
  std::list<Employee *> _subordinates;
};

inline std::ostream &operator<<(std::ostream &stream,
                                const Employee &employee) {
  const auto is_manager = !employee._subordinates.empty();
  return stream << employee._name << " (salary: " << employee._salary
                << "| manager: " << (is_manager ? "yes" : "no") << ")";
}
