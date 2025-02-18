#include "LinkedList.hpp"

LinkedList::LinkedList(const LinkedList& other)
{
    auto parcours = other._front;
    for (; parcours != nullptr; parcours = parcours->_next)
    {
        push_back(parcours->value());
    }
}

LinkedList::LinkedList(LinkedList&& other)
{
    _front      = other._front;
    _back       = other._back;
    other._back = other._front = nullptr;
    other._size                = 0;
}

LinkedList::LinkedList()
{}

LinkedList::~LinkedList()
{
    auto parcours = _front;
    for (; parcours != nullptr;)
    {
        auto next = parcours->_next;
        delete parcours;
        parcours = next;
    }
}

size_t LinkedList::size() const
{
    return _size;
}

bool LinkedList::empty() const
{
    return _size == 0;
}

void LinkedList::push_back(const Person& p1)
{
    auto newBack = new Link(_back, p1);
    if (_back != nullptr)
        _back->_next = newBack;
    _back = newBack;
    if (_front == nullptr)
    {
        _front = newBack;
    }
    _size++;
}

void LinkedList::push_back(Person&& p1)
{
    auto newBack = new Link(_back, std::move(p1));
    if (_back != nullptr)
        _back->_next = newBack;
    _back = newBack;
    if (_front == nullptr)
    {
        _front = newBack;
    }
    _size++;
}

Person& LinkedList::back() const
{
    return _back->value();
}

Person& LinkedList::front() const
{
    return _front->value();
}

std::ostream& operator<<(std::ostream& o, const LinkedList& list)
{
    o << "{";
    auto parcours = list._front;

    for (; parcours; parcours = parcours->_next)
    {
        o << " " << parcours->value();
        if (parcours->_next)
        {
            o << ",";
        }
    }
    o << " }";
    return o;
}

void LinkedList::concatenate_back(const LinkedList& other)
{
    auto parcours = other._front;
    for (; parcours != nullptr; parcours = parcours->_next)
    {
        push_back(parcours->value());
    }
}

void LinkedList::concatenate_back(LinkedList&& other)
{
    _back->_next = other._front;
    _back        = other._back;
    other._front = other._back = nullptr;
    other._size                = 0;
}

void LinkedList::swap(LinkedList& l1, LinkedList& l2)
{
    auto new_l1_front = l2._front;
    l2._front         = l1._front;
    l1._front         = new_l1_front;
    auto new_l1_back  = l2._back;
    l2._back          = l1._back;
    l1._back          = new_l1_back;
}

bool LinkedList::contains(const Person& other) const
{
    auto parcours = _front;
    for (; parcours != nullptr; parcours = parcours->_next)
    {
        if (parcours->value() == other)
        {
            return true;
        }
    }
    return false;
}

void LinkedList::push_back_if_absent(const Person& p1)
{
    if (!contains(p1))
    {
        push_back(p1);
    }
}

void LinkedList::push_back_if_absent(Person&& p1)
{
    if (!contains(p1))
    {
        push_back(std::move(p1));
    }
}
