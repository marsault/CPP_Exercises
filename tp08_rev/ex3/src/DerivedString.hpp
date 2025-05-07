#pragma once
#include "Base.hpp"

#include <memory>
#include <string>

class DerivedString : public Base
{
public:
    DerivedString(std::string value)
        : _value { std::move(value) }
        , Base("String")
    {}

    bool is_null() const override { return _value == ""; }

    const std::string& data() const { return _value; }

    std::string to_string() const override { return _value; }

    bool operator==(const Base& base) const override
    {
        if (!(base.type() == "String"))
        {
            return false;
        }
        return base.to_string() == to_string();
    }

    std::unique_ptr<Base> copy() const override { return std::make_unique<DerivedString>(*this); }

    std::unique_ptr<Base> move() override { return std::make_unique<DerivedString>(std::move(*this)); }

private:
    std::string _value;
};