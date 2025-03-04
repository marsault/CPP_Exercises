#pragma once

#include <memory>
#include <string>

class DerivedString;
class DerivedInt;

class Base
{
public:
    Base()
        : Base("None")
    {}

    Base(std::string type)
        : _type { type }
    {}

    std::string const&            type() const { return _type; }
    virtual bool                  is_null() const   = 0;
    virtual std::string           to_string() const = 0;
    virtual std::unique_ptr<Base> new_copy() const  = 0;
    virtual std::unique_ptr<Base> new_move()        = 0;

    bool operator==(const Base& other) const
    {
        if (other.type() != this->type())
            return false;
        return (is_equal_assuming_same_type(other));
    }

    // Nécessaire pour éviter les fuites mémoires dans DerivedList.
    virtual ~Base() noexcept = default;

protected:
    virtual bool is_equal_assuming_same_type(const Base& b) const = 0;

private:
    std::string _type;
};

inline std::ostream& operator<<(std::ostream& o, const Base& b)
{
    return o << b.to_string();
}

#define JAI_LU_LE_WARNING_09 true
#define JAI_LU_LE_WARNING_13 true