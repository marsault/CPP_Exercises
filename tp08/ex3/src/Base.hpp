#pragma once

#include <memory>
#include <ostream>
#include <string>
#define JAI_LU_LE_WARNING_09 true
#define JAI_LU_LE_WARNING_13 true
class Base
{
public:
    Base(std::string type)
        : _type { std::move(type) }
    {}

    virtual ~Base()                                             = default;
    virtual bool                  is_null() const               = 0;
    virtual std::string           to_string() const             = 0;
    virtual bool                  operator==(const Base& other) = 0;
    std::string                   type() const { return _type; }
    virtual std::unique_ptr<Base> clone() const = 0;
    virtual std::unique_ptr<Base> move()        = 0;

private:
    std::string _type;
};

std::ostream& operator<<(std::ostream& op, Base& base)
{
    op << base.to_string();
    return op;
}
