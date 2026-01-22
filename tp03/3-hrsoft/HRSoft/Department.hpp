#pragma once

#include "Employee.hpp"

#include <iostream> // cout
#include <list>
#include <string>

class Department
{
public:
  Department(const std::string& name) : _name{name} {}

  Employee& add_employee(const std::string& name, unsigned int salary,
                         Employee* manager)
  {
    auto& employee = _employees.emplace_back(name, salary);

    if (manager != nullptr)
      manager->add_subordinate(employee);

    return employee;
  }

    // Exercice 3.2
    void print_employees() const 
    {
        std::cout << _name << " department's employees: " << std::endl;
        for(const auto& emp: _employees)
        {
            std::cout << emp << std::endl;
        }
    }

    // supprime l'employé donné; renvoie true si ça a fonctionné, false sinon
    bool remove_employee(const Employee& emp) 
    {
        auto it=_employees.begin();

        for(; it!=_employees.end(); ++it) 
            if(it->get_name() == emp.get_name())
                break;

        if(it == _employees.end())
            return false;
        
        // employé trouvé, signalons d'abord à ses managers son licenciement...
        for(auto& manager: _employees) 
            manager.remove_subordinate(emp);

        // ... puis supprimons-le
        _employees.erase(it);
        return true;
    }

    friend std::ostream& operator<<(std::ostream&, const Department&);
    friend class HRSoftSystem;  // Bonus
    
    // Bonus
    std::string get_name() const { return _name; }

    // Renvoie un pointeur vers l'employé dont le nom est fourni, ou nullptr s'il n'existe pas.
    Employee* find_employee(const std::string& name) 
    {
        for(auto& emp: _employees)
            if(emp.get_name() == name)
                return &emp;

        return nullptr;
    }


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
