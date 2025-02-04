#include "LinkedList.hpp"

LinkedList::LinkedList(const LinkedList& other)
{
    for (Link* it = other._front; it != nullptr; it = it->_next)
        push_back(it->value());
}

LinkedList::LinkedList(LinkedList&& other)
    : _front { other._front }
    , _back { other._back }
    , _size { other._size }
{
    // other doit être remis dans un état cohérent.
    other.clear_without_dealloc();
}

LinkedList& LinkedList::operator=(const LinkedList& other)
{
    if (this != &other)
    {
        clear();
        for (Link* it = other._front; it != nullptr; it = it->_next)
            push_back(it->value());
    }
    return (*this);
}

LinkedList& LinkedList::operator=(LinkedList&& other)
{
    if (this != &other)
    {
        clear();
        _front = other._front;
        _back  = other._back;
        _size  = other._size;

        // other doit être remis dans un état cohérent.
        other.clear_without_dealloc();
    }
    return (*this);
}

LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::clear_without_dealloc()
{
    _front = nullptr;
    _back  = nullptr;
    _size  = 0;
}

void LinkedList::clear()
{
    // On utilise oldit pour ne pas accéder à de la mémoire désalloué.
    Link* oldit = nullptr;
    for (Link* it = _front; it != nullptr; it = it->_next)
    {
        delete oldit;
        oldit = it;
    }
    delete oldit;
    clear_without_dealloc();
}

bool LinkedList::empty() const
{
    return _front == nullptr;
}

size_t LinkedList::size() const
{
    size_t res = 0;
    for (Link* it = _front; it != nullptr; it = it->_next)
        ++res;
    return res;
}

void LinkedList::push_back(Person p)
{
    Link* new_back = new Link { _back, std::move(p) };
    if (_back == nullptr)
        _front = new_back;
    else
        _back->_next = new_back;
    _back = new_back;
}

std::ostream& operator<<(std::ostream& o, const LinkedList& list)
{
    if (list.empty())
        return o << "{ }";
    o << "{ ";
    bool first = true;
    for (Link* it = list._front; it != nullptr; it = it->_next)
    {
        if (first)
            first = false;
        else
            o << ", ";
        o << it->value();
    }
    return o << " }";
}

void LinkedList::concatenate_back(LinkedList other)
{
    if (!other.empty())
    {
        if (_front == nullptr)
            (*this) = std::move(other);
        else
        {
            _back->_next        = other._front;
            other._front->_prev = _back;
            _back               = other._back;

            // Pour que la destruction de other à la fin de la
            // fonction ne supprime pas les Link
            other.clear_without_dealloc();
        }
    }
}

bool LinkedList::contains(Person const& p) const
{
    for (Link* it = _front; it != nullptr; it = it->_next)
        if (it->value() == p)
            return true;
    return false;
}

void LinkedList::push_back_if_absent(const Person& p)
{
    if (!contains(p))
        push_back(p);
}

void LinkedList::push_back_if_absent(Person&& p)
{
    if (!contains(p))
        push_back(std::move(p));
}

void LinkedList::swap(LinkedList& l, LinkedList& r)
{
    LinkedList tmp = std::move(l);

    l = std::move(r);
    r = std::move(tmp);
}