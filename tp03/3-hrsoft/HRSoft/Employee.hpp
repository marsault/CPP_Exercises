#pragma once

#include <iostream>
#include <list>
#include <ostream>
#include <string>

class Employee
{
public:
    Employee(const std::string& name, unsigned int salary)
        : _name { name }
        , _salary { salary } {}

    void add_subordinate(Employee& subordinate) { _subordinates.push_back(&subordinate); }

    friend std::ostream& operator<<(std::ostream&, const Employee&);

    void print_subordinates() const {
        std::cout << "Subordinates of " << _name << ":" << std::endl;
        for (const auto& subordinate : _subordinates)
        {
            std::cout << "  - " << *subordinate << std::endl;
        }
    }

    bool operator==(const Employee& other) const { return _name == other._name && _salary == other._salary; }

    void remove_subordinate(Employee& subordinate) { _subordinates.remove(&subordinate); }

    const std::string& get_name() const { return _name; }

    bool is_manager() const { return !_subordinates.empty(); }

private:
    std::string          _name;
    unsigned int         _salary = 0;
    std::list<Employee*> _subordinates;
};

inline std::ostream& operator<<(std::ostream& stream, const Employee& employee) {
    const auto is_manager = !employee._subordinates.empty();
    return stream << employee._name << " (salary: " << employee._salary
                  << "| manager: " << (is_manager ? "yes" : "no") << ")";
}
