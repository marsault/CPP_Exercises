#pragma once
#include <array>
#include <forward_list>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <typename Type, int _size>
class HybridArray
{

public:
    HybridArray() = default;

    template <typename... Args>
    HybridArray(Args&&... args)
        : HybridArray()
    {
        (push_back(std::forward<Args>(args)), ...);
    }

    static constexpr int static_size() { return _size; }

    Type& push_back(const Type& newElem)
    {
        std::cout << currentSize << " " << newElem << std::endl;

        if (currentSize == _size)
        {
            std::cout << "moove all" << std::endl;
            for (auto i = 0; i < _size; i++)
            {
                vector.emplace_back(std::move(array[i]));
            }
            currentSize++;
            return vector.emplace_back(newElem);
        }
        if (currentSize > _size)
        {
            std::cout << "in vector" << std::endl;
            currentSize++;
            return vector.emplace_back(newElem);
        }
        std::cout << "in array" << std::endl;
        array[currentSize] = newElem;
        currentSize++;
        return array[currentSize - 1];
    }

    int size() const { return currentSize; }

    const Type& operator[](int index) const
    {
        if (currentSize <= _size)
        {
            return array[index];
        }
        return vector[index];
    }

    Type& operator[](int index)
    {
        if (currentSize <= _size)
        {
            return array[index];
        }
        return vector[index];
    }

private:
    int                     currentSize = 0;
    std::vector<Type>       vector;
    std::array<Type, _size> array;
};

template <typename Type>
class HybridArray<Type, 0> : public std::vector<Type>
{
public:
    HybridArray() = default;
    using std::vector<Type>::vector;
};
