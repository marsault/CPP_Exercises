#include "Link.hpp"
#include "Person.hpp"



Link::Link(const Person& p1): _value{p1}{}

Link::Link(Person&& p1): _value{std::move(p1)}{}

Link::Link(Link* prev, const Person& p1) : _value{p1}, _prev{prev}{
}

Link::Link(Link* prev, Person&& p1) : _value{std::move(p1)}, _prev{prev}{
}

Person& Link::value() {
    return _value;
}

const Person& Link::value() const {
    return _value;
}

