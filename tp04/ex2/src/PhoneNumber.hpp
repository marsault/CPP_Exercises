#pragma once // test 07

#include <ostream> // test 11
// #include <vector>

class PhoneNumber
{
private:
    int                  _numbers[5];
    friend std::ostream& operator<<(std::ostream& sortie, const PhoneNumber& pn); // test 11

public:
    // test 01
    PhoneNumber(int i1, int i2, int i3, int i4, int i5)
        : _numbers { i1, i2, i3, i4, i5 }
    {}

    // test 02
    bool is_valid() const /* <- test 03 */
    {
        for (const auto& num : _numbers)
            if (num < 0 or num > 99)
                return false;
        return true;
    }

    // test 04
    int operator[](int i) const /* <- test 06 */
    {
        if (i < 0 or i > 4) // <- test 05
            return -1;
        return _numbers[i]; //.at(i);
    }
};

// tests 11, 12, 13
std::ostream& operator<<(std::ostream& sortie, const PhoneNumber& pn)
{
    for (const auto& num : pn._numbers)
    {
        if (num < 10) // test 12
            sortie << 0;
        sortie << num;
    }
    return sortie;
}
