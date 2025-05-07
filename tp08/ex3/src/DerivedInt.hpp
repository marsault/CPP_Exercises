#pragma once
#include "Base.hpp"

#include <memory>

class DerivedInt : public Base
{

public:
    DerivedInt(int value)
        : _value { value }
        , Base("Int")
    {}

    int  data() const { return _value; }
    bool is_null() const override { return _value == 0; }

    std::string to_string() const override { return std::to_string(_value); }

    bool operator==(const Base& other) override
    {
        if (other.type() != "Int")
        {
            return false;
        }

        return std::to_string(_value) == other.to_string();
    }
    std::unique_ptr<Base> clone() const override { return std::make_unique<DerivedInt>(*this); }
    std::unique_ptr<Base> move() override { return std::make_unique<DerivedInt>(std::move(*this)); }

private:
    int _value;
};