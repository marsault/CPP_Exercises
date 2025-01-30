//#pragma once

#include "PhoneBookEntry.hpp"
#include <list>

#include <vector>
// test 31: une classe PhoneBook entièrement vide suffit
class PhoneBook {
    private:
        // test 32
        std::list<PhoneBookEntry> _entries;

    public:
        // test 32: le type de retour peut être void
        // ... mais doit devenir bool pour le test 34
        inline bool add_entry(const PhoneBookEntry& entry) 
        { 
            // tests 34, 35
            if
            (
                !(entry.get_number().is_valid()) // test 34
                or get_number(entry.get_name()) != nullptr // test 35 (chercher le nom suffisait, mais ceci nous évite de réécrire du code)
            )
                return false;
            _entries.emplace_back(entry); // cette ligne suffit pour le test 32
            return true;
        }

        // test 34
        inline const PhoneNumber* get_number(const std::string& nom) const 
        {
            for(auto& entry: _entries)
                if(entry.get_name() == nom)
                    return &(entry.get_number());
            return nullptr;
        }

};
