#pragma once                // test 32
#include "PhoneNumber.hpp"

class PhoneBookEntry {
    private:
        std::string _nom;
        PhoneNumber _numero;

    public:
        // test 21
        inline PhoneBookEntry(const std::string& nom, const PhoneNumber& numero) : _nom(nom), _numero(numero) { } 

        // test 22
        // les & sont pour le test 23
        // les const sont pour le test 24; si la fonction-membre est const, alors le type renvoyé doit l'être aussi
        inline const std::string& get_name()   const { return _nom; }
        inline const PhoneNumber& get_number() const { return _numero; }


        // test 25
        inline int operator==(const PhoneBookEntry& autre) const /* <- test 26 */ 
        { 
            return _nom == autre._nom;
        }

};
