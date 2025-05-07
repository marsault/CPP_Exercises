#pragma once
#include "../lib/Tracker.hpp"

#include <memory>
#include <string>

class StringInstancePair
{

public:
    StringInstancePair(std::string str)
        : _str { std::move(str) }
        , _tracker { std::make_unique<Tracker>(Tracker()) }
    {}

    ~StringInstancePair() = default;

    StringInstancePair& operator=(const StringInstancePair& other) = default;

    StringInstancePair(const StringInstancePair& other)
        : _str { other._str }
        , _tracker { std::make_unique<Tracker>(*other._tracker) }

    {}

    StringInstancePair(StringInstancePair&& other) = default;

    StringInstancePair& operator=(StringInstancePair&& other) = default;

    const std::string& get_str() const { return _str; }

    const Tracker& get_tracker() const { return *_tracker; }

private:
    std::string              _str;
    std::unique_ptr<Tracker> _tracker;
};
