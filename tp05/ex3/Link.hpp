#pragma once

#include "Person.hpp"

class LinkedList;

class Link
{
public:
    // Il faut réflechir aux prototypes des fonctions-membres ci-dessous, certains ne sont pas corrects.
    Link(const Person&);
    Link(Person&&);
    Person& value();
    const Person& value() const;
    Link(Link*, const Person&);
    Link(Link*, Person&&);
    Link(Link*, Person, Link*);
    Link*  _prev;
    Link*  _next;
    Person _value;
};