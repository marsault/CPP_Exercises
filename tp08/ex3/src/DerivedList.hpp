#pragma once

#include "Base.hpp"

#include <memory>
#include <string>
#include <vector>

class DerivedList : public Base
{

public:
    DerivedList()
        : Base { "List" }
    {}

    DerivedList(const DerivedList& other)
        : DerivedList()
    {
        for (auto& e : other._values)
            add(*e);
    }

    DerivedList(DerivedList&& other) = default;

    std::string to_string() const override
    {
        std::string result { "[" };
        auto        first = true;
        for (const auto& val : _values)
        {

            if (first)
            {
                first = false;
            }
            else
            {
                result += ",";
            }
            result += val.get()->to_string();
        }
        result += "]";
        return result;
    }

    bool is_null() const override { return _values.empty(); }

    bool operator==(const Base& other) override
    {
        if (other.type() != "List")
        {
            return false;
        }

        return other.to_string() == to_string();
    }

    void add(const Base& base) { _values.emplace_back(base.clone()); }

    void add(Base&& base) { _values.emplace_back(base.move()); }

    std::unique_ptr<Base> clone() const override { return std::make_unique<DerivedList>(*this); }

    std::unique_ptr<Base> move() override { return std::make_unique<DerivedList>(std::move(*this)); }

private:
    std::vector<std::unique_ptr<Base>> _values;
};
