#include <iostream>
#pragma once

void print_hello();

inline void print_bye() {
    std::cout << "Bye" << std::endl;
}
