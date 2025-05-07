#include "PhoneNumber.hpp"

#include <string>
#pragma once

class PhoneBookEntry
{
private:
    std::string _name;
    PhoneNumber _phoneNumber;

public:
    PhoneBookEntry(const std::string& name, const PhoneNumber& PhoneNumber)
        : _name { name }
        , _phoneNumber { PhoneNumber } {};

    const std::string& get_name() const { return _name; }
    const PhoneNumber& get_number() const { return _phoneNumber; }

    bool operator==(const PhoneBookEntry& op) const { return _name == op._name; }
};