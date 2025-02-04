#pragma once

#include "Link.hpp"
#include "Person.hpp"

class LinkedList
{
public:
    friend std::ostream& operator<<(std::ostream& o, const LinkedList& list);
    // Il faut réflechir aux prototypes des fonctions-membres ci-dessous, certains ne sont pas corrects.

    size_t size() const;
    bool   empty() const;
    void   push_back(Person);

    Person&       back() { return _back->value(); }
    const Person& back() const { return _back->value(); }
    Person&       front() { return _front->value(); }
    const Person& front() const { return _front->value(); }

    bool contains(Person const&) const;

    void concatenate_back(LinkedList);

    void push_back_if_absent(const Person&);
    void push_back_if_absent(Person&&);

    ~LinkedList();

    LinkedList(const LinkedList&);
    LinkedList(LinkedList&&);

    LinkedList& operator=(const LinkedList&);
    LinkedList& operator=(LinkedList&&);

    LinkedList() = default;

    void clear();

    static void swap(LinkedList&, LinkedList&);

private:
    Link* _front = nullptr;
    Link* _back  = nullptr;
    int   _size  = 0;

    void clear_without_dealloc();
};