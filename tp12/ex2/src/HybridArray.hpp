#pragma once
#include <algorithm>
#include <array>
#include <functional>
#include <memory>
#include <vector>

template <typename Type, int NB>
class HybridArray
{
public:
    HybridArray() = default;

    template <typename... Args>
    HybridArray(Args&&... args)
    {
        (push_back(std::forward<Args>(args)), ...);
    }

    // ~HybridArray();

    static constexpr int static_size() { return NB; }

    Type& push_back(Type newElem)
    {
        nb_elements++;
        if (nb_elements == NB + 1)
        {
            for (auto& elem : _array)
            {
                _vector.emplace_back(std::move(elem));
            }

            return _vector.emplace_back(newElem);
        }
        if (nb_elements <= NB)
        {
            _array[nb_elements - 1] = newElem;
            return _array[nb_elements - 1];
        }
        return _vector.emplace_back(newElem);
    }

    int size() const { return nb_elements; }

    const Type& operator[](int index) const
    {
        if (nb_elements <= NB)
        {
            return _array[index];
        }
        return _vector.at(index);
    }

    Type& operator[](int index)
    {
        if (nb_elements <= NB)
        {
            return _array[index];
        }
        return _vector.at(index);
    }

private:
    int                  nb_elements = 0;
    std::array<Type, NB> _array;
    std::vector<Type>    _vector;
};

template <typename Type>
class HybridArray<Type, 0> : public std::vector<Type>
{
public:
    HybridArray() = default;

    using std::vector<Type>::vector;

    static constexpr int static_size() { return 0; }
};