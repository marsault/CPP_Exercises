#pragma once

#include "Tracker.hpp"

#include <iostream>
#include <string>

class Person
{
    friend std::ostream& operator<<(std::ostream& o, const Person& p);

public:
    Person(std::string given_name, std::string family_name)
        : _given_name { std::move(given_name) }
        , _family_name { std::move(family_name) }
    {}

    void operator++() { _age++; }

    bool operator==(const Person& other);

private:
    std::string _given_name;
    std::string _family_name;
    int         _age = 0;
    Tracker     _tracker;
};
