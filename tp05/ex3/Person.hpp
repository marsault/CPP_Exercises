#pragma once

#include "Tracker.hpp"

#include <iostream>
#include <string>

class Person
{
    friend std::ostream& operator<<(std::ostream& o, Person p);

public:
    Person(std::string given_name, std::string family_name)
        : _given_name { given_name }
        , _family_name { family_name }
    {}

    void operator++() { _age++; }

    bool operator==(Person other);

private:
    std::string _given_name;
    std::string _family_name;
    int         _age = 0;
    Tracker     _tracker;
};
