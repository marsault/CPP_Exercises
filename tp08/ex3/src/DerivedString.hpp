#pragma once

#include "Base.hpp"

#include <memory>
#include <string>

class DerivedString : public Base
{
public:
    DerivedString(std::string d)
        : Base("String")
        , _data { d }
    {}

    std::string const& data() { return _data; }
    bool               is_null() const override { return _data == ""; }
    std::string        to_string() const override { return _data; }

    std::unique_ptr<Base> new_copy() const override { return std::make_unique<DerivedString>(*this); }
    std::unique_ptr<Base> new_move() override { return std::make_unique<DerivedString>(std::move(*this)); }

protected:
    virtual bool is_equal_assuming_same_type(const Base& b) const override
    {
        return (dynamic_cast<const DerivedString&>(b)._data == _data);
    }

private:
    std::string _data;
};