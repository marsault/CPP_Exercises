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

    // Exercice 3.4
    void remove_employee(Employee& emp) 
    {
        // parcourir les départements à la recherche de l'employé, et le supprimer; comme un 
        // employé travaille pour un seul département, on s'arrête après la première tentative fructueuse
        for(auto& dep: _departments)
            if(dep.remove_employee(emp))
            {
                std::cout << "removed employee " << emp.get_name() << std::endl;
                dep.print_employees();
                break;         
            }
                
    }

    // Bonus

    // Renvoie un pointeur vers le département dont le nom est fourni, ou nullptr s'il n'existe pas.
    Department* find_department(const std::string& name) 
    {
        std::cout << "[DEBUG] looking for department " << name << "... ";
        for(auto it=_departments.begin(); it!=_departments.end(); ++it)
            if(it->get_name() == name)
            {
                std::cout << "found." << std::endl;
                return &(*it);
            }

        std::cout << "not found." << std::endl;
        return nullptr;
    }

    // Renvoie un pointeur vers l'employé dont le nom est fourni, ou nullptr s'il n'existe pas.
    Employee* find_employee(const std::string& name) 
    {
        for(auto& dep: _departments)
            // for(auto& emp: dep._employees)
                // if(emp.get_name() == name)
                    // return &emp;
            for(auto it=dep._employees.begin(); it!=dep._employees.end(); ++it)
                if(it->get_name() == name)
                    return &(*it);


        return nullptr;
    }

    // Déplace l'employé name vers le département target_name
    void move_employee(const std::string& target_name, const std::string& name)
    {
#define DBG
#ifdef DBG
        std::cout << "moving " << name << " to " << target_name << std::endl;
        // BUG SEGFAULT
#endif
        // récupérer l'employé et le département ciblé
        auto* emp = find_employee(name);
#ifdef DBG
        std::cout << "so far so good" << std::endl;
#endif
        auto* new_dpt = find_department(target_name);
        // pour l'ajout, on doit récupérer le salaire et le manager
        auto salary = emp->get_salary();
        // pour récupérer le manager, on doit parcourir tous les départements
        Employee* manager = nullptr;
        for(auto& dep: _departments)
            for(auto& member: dep._employees)
                if(member.manages(*emp))
                {
                    manager = &member;
                    break;
                }
#ifdef DBG
        std::cout << "so far so good" << std::endl;
#endif

        new_dpt->add_employee(name, salary, manager);
        // retirer la référence à l'employé dans son ancien département (qui n'est pas nécessairement 
        // celui de son manager)
        for(auto& former_dep: _departments) 
        {
            auto it = former_dep._employees.begin();
            for(; it!=former_dep._employees.end(); ++it)
                if(it->get_name() == name)
                    break;
            if(it!=former_dep._employees.end())
            {
                former_dep._employees.erase(it);
                break;
            }
        }   
    }

private:
    std::list<Department> _departments;
};
