#include "Link.hpp"

Link::Link(Person p)
    : _value { std::move(p) }
{}

Link::Link(Link* prev, Person p)
    : _prev { prev }
    , _value { std::move(p) }
{}

Link::Link(Link* prev, Person p, Link* next)
    : _prev { prev }
    , _next { next }
    , _value { std::move(p) }
{}

const Person& Link::value() const
{
    return _value;
}

Person& Link::value()
{
    return _value;
}
