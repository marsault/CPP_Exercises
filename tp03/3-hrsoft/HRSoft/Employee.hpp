#pragma once

#include <algorithm> // find
#include <iostream> // cout
#include <list>
#include <ostream>
#include <string>

class Employee
{
public:
  Employee(const std::string& name, unsigned int salary)
      : _name{name}, _salary{salary}
  {}

    void add_subordinate(Employee& subordinate)
    {
        // Q3
        // l'architecture A spécifie que les subordonnés sont des *références* aux employés, on 
        // ajoute donc la *référence* à subordinate à notre liste plutôt que le subordinate
        _subordinates.push_back(&subordinate);
    }

    // Exercice 3.3
    void print_subordinates() const
    {
        std::cout << _name << "'s subordinates are:" << std::endl;
        for(const auto& sub: _subordinates)
        {
            // _subordinates contient des Employee*, il faut donc déréférencer sub pour afficher son
            // contenu plutôt que sa valeur (= adresse)
            std::cout << "    - " << *sub << std::endl;
        }
    }

    // Exercice 3.4
    void remove_subordinate(const Employee& sub)
    {
        // trouver la référence à sub parmi les subordonnés
        auto it = std::find(_subordinates.begin(), _subordinates.end(), &sub);
        // la supprimer de la liste si elle y est
        if(it!=_subordinates.end())
        {
            _subordinates.erase(it);
        }
    }

    // Exercice 3.4
    /*
     *  Renvoie true si other est un subordonné de l'employé, false sinon.
     */
    bool manages(const Employee& other) const
    {
        auto it = std::find(_subordinates.begin(), _subordinates.end(), &other);
        return it != _subordinates.end();
    }

  friend std::ostream& operator<<(std::ostream&, const Employee&);

    const std::string& get_name() const 
    { 
        return _name; 
    };

    unsigned int get_salary() const 
    { 
        return _salary; 
    };


private:
  std::string _name;
  unsigned int _salary = 0;
  std::list<Employee*> _subordinates;
};

inline std::ostream& operator<<(std::ostream& stream, const Employee& employee)
{
  const auto is_manager = !employee._subordinates.empty();
  return stream << employee._name << " (salary: " << employee._salary
                << "| manager: " << (is_manager ? "yes" : "no") << ")";
}
