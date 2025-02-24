#pragma once

#include "Object.hpp"

#include <utility>

class CopyablePtr
{
public:
    // We allow to create a null CopyablePtr;
    CopyablePtr() = default;

    CopyablePtr(int value)
        : _obj{new Object{value}}
    {
    }

    CopyablePtr(const CopyablePtr &other)
        : _obj{other == nullptr ? nullptr : new Object{*other}}
    {
    }

    CopyablePtr(CopyablePtr &&other)
        : _obj{other._obj}
    {
        // We now manage the Object pointed by other
        // We need to set the pointer of other to nullptr in order to avoir double-deallocation
        other._obj = nullptr;
    }

    ~CopyablePtr()
    {
        // We do not need to check if _obj == nullptr
        // Deleting a nullptr does nothing
        delete _obj;
    }

    bool operator==(std::nullptr_t) const { return _obj == nullptr; }

    Object &operator*() const { return *_obj; }

    // This operator allows to assign a nullptr to a CopyablePtr
    CopyablePtr &operator=(std::nullptr_t)
    {
        delete _obj;
        _obj = nullptr;
        return *this;
    }

    CopyablePtr &operator=(const CopyablePtr &other)
    {
        if (this != &other)
        {
            delete _obj;
            _obj = ((other == nullptr) ? nullptr : new Object{*other});
        }
        return *this;
    }

    CopyablePtr &operator=(CopyablePtr &&other)
    {
        if (this != &other)
        {
            delete _obj;
            _obj = other._obj;
            other._obj = nullptr;
        }
        return *this;
    }

private:
    Object *_obj = nullptr;
};