#pragma once

#include "Person.hpp"

class LinkedList;

class Link
{
    friend LinkedList; // On autorise LinkedList à modifier Link;
public:
    Link(Person);

    Person&       value();
    const Person& value() const;
    Link(Link*, Person);
    Link(Link*, Person, Link*);
    Link*  _prev = nullptr;
    Link*  _next = nullptr;
    Person _value;
};