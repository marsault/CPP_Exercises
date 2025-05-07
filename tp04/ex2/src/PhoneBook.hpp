#pragma once
#include "PhoneBookEntry.hpp"

#include <list>
#include <string>

class PhoneBook
{
private:
    std::list<PhoneBookEntry> _phoneBooks;

public:
    bool add_entry(const PhoneBookEntry& phoneBook)
    {
        if (!phoneBook.get_number().is_valid())
        {
            return false;
        }
        for (const auto& _phoneBook : _phoneBooks)
        {
            if (_phoneBook == phoneBook)
            {
                return false;
            }
        }
        _phoneBooks.emplace_back(phoneBook);
        return true;
    }

    const PhoneNumber* get_number(const std::string& name) const
    {

        for (const auto& phoneBook : _phoneBooks)
        {
            if (phoneBook.get_name() == name)
            {
                return &phoneBook.get_number();
            }
        }
        return nullptr;
    }
};