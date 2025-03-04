#include "../lib/Tracker.hpp"

#include <memory>
#include <string>

class StringInstancePair
{
public:
    StringInstancePair(std::string s)
        : _str(std::move(s))
        , _tracker(std::make_unique<Tracker>())
    {}

    StringInstancePair(StringInstancePair&& other) = default;

    StringInstancePair(const StringInstancePair& other)
        : _str { other._str }
        , _tracker { std::make_unique<Tracker>(other.get_tracker()) }
    {}

    const Tracker&     get_tracker() const { return *_tracker; }
    const std::string& get_str() const { return _str; }

private:
    std::string              _str;
    std::unique_ptr<Tracker> _tracker;
};