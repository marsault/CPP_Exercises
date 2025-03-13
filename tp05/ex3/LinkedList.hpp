#pragma once

#include "Link.hpp"
#include "Person.hpp"

class LinkedList
{
public:
    // Il faut réflechir aux prototypes des fonctions-membres ci-dessous, certains ne sont pas corrects.
    friend std::ostream& operator<<(std::ostream& o, const LinkedList& list);

    LinkedList();
    LinkedList(const LinkedList&);
    LinkedList(LinkedList&&);
    size_t      size() const;
    bool        empty() const;
    void        push_back(const Person&);
    void        push_back(Person&&);
    Person&     back() const;
    Person&     front() const;
    void        concatenate_back(const LinkedList&);
    void        concatenate_back(LinkedList&&);
    static void swap(LinkedList&, LinkedList&);
    bool        contains(const Person&) const;
    void        push_back_if_absent(const Person&);
    void        push_back_if_absent(Person&&);

    // void concatenate_back(LinkedList);

    // bool contains(Person);

    // void push_back_if_absent(Person);

    // static void swap(LinkedList, LinkedList);

    ~LinkedList();

private:
    Link* _front = nullptr;
    Link* _back  = nullptr;
    int   _size  = 0;
};