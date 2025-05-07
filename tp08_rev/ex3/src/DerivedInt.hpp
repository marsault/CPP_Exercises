#pragma once
#include "Base.hpp"

class DerivedInt : public Base
{
public:
    DerivedInt(int value)
        : _value { value }
        , Base("Int")
    {}

    bool is_null() const override { return _value == 0; }

    int data() const { return _value; }

    std::string to_string() const override { return std::to_string(_value); }

    bool operator==(const Base& base) const override
    {
        if (!(base.type() == "Int"))
        {
            return false;
        }
        return base.to_string() == to_string();
    }

    std::unique_ptr<Base> copy() const override { return std::make_unique<DerivedInt>(*this); }

    std::unique_ptr<Base> move() override { return std::make_unique<DerivedInt>(std::move(*this)); }

private:
    int _value;
};