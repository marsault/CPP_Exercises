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

    const std::string& data() const { return _value; }
    bool               is_null() const override { return _value == ""; }

    std::string to_string() const override { return _value; }

    bool operator==(const Base& other) override
    {
        if (other.type() != "String")
        {
            return false;
        }

        return _value == other.to_string();
    }

    std::unique_ptr<Base> clone() const override { return std::make_unique<DerivedString>(*this); }
    std::unique_ptr<Base> move() override { return std::make_unique<DerivedString>(std::move(*this)); }

private:
    std::string _value;
};