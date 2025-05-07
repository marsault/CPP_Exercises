#include <ostream>
#include <string>
#include <vector>
#pragma once

class PhoneNumber
{
private:
    std::vector<int> _nbrs;

public:
    PhoneNumber(int un, int deux, int trois, int quatre, int cinq)
        : _nbrs { std::vector { un, deux, trois, quatre, cinq } } {};

    bool is_valid() const
    {
        for (int i = 0; i < 5; i++)
        {
            if (_nbrs[i] < 0 || _nbrs[i] > 99)
            {
                return false;
            }
        }
        return true;
    }

    int operator[](int index) const
    {
        if (index >= 0 && index < 5)
        {
            return _nbrs[index];
        }
        return -1;
    }

    friend std::ostream& operator<<(std::ostream& op, const PhoneNumber& phone)
    {
        for (auto& i : phone._nbrs)
        {
            if (i < 10)
            {
                op << 0;
            }
            op << i;
        }
        return op;
    }
};
