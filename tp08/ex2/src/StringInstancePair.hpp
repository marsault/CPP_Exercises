#pragma once
#include "../lib/Tracker.hpp"

#include <memory>
#include <string>

class StringInstancePair
{
private:
    std::unique_ptr<Tracker> _tracker;
    std::string              _string;

public:
    StringInstancePair(std::string string)
        : _string { std::move(string) }
        , _tracker { std::make_unique<Tracker>() }
    {}

    ~StringInstancePair() = default;

    StringInstancePair(StringInstancePair&& other) = default;

    StringInstancePair(const StringInstancePair& other)
        : _string { other._string }
        , _tracker { std::make_unique<Tracker>(*other._tracker) }
    {}

    StringInstancePair& operator=(const StringInstancePair& other) = default;

    const Tracker&     get_tracker() const { return *_tracker; }
    const std::string& get_str() const { return _string; }
};
