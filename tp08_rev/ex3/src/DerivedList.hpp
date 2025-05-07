#pragma once
#include "Base.hpp"

#include <memory>
#include <string>
#include <vector>

class DerivedList : public Base
{
public:
    DerivedList()
        : Base("List")

    {}

    DerivedList(const DerivedList& other)
        : Base("List")
    {
        for (auto& val : other._value)
        {
            _value.emplace_back(val->copy());
        }
    }

    ~DerivedList() = default;

    DerivedList& operator=(const DerivedList& other) = default;

    DerivedList(DerivedList&& other) = default;

    DerivedList& operator=(DerivedList&& other) = default;

    bool is_null() const override { return _value.empty(); }

    std::string to_string() const override
    {
        std::string result = "[";
        auto        first  = true;
        for (auto& base : _value)
        {
            if (!first)
            {
                result += ",";
            }
            result += base.get()->to_string();
            first = false;
        }
        result += "]";
        return result;
    }

    bool operator==(const Base& base) const override
    {
        if (!(base.type() == "List"))
        {
            return false;
        }
        return base.to_string() == to_string();
    }

    void add(Base& base) { _value.emplace_back(base.copy()); }

    void add(Base&& base) { _value.emplace_back(base.move()); }

    std::unique_ptr<Base> copy() const override { return std::make_unique<DerivedList>(*this); }

    std::unique_ptr<Base> move() override { return std::make_unique<DerivedList>(std::move(*this)); }

private:
    std::vector<std::unique_ptr<Base>> _value = std::vector<std::unique_ptr<Base>>();
};