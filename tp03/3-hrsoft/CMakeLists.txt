cmake_minimum_required(VERSION 3.16)
project(hrsoft)

add_executable(hrsoft-tests
    HRSoftTests.cpp
    HRSoft/HRSoftSystem.hpp
    HRSoft/Department.hpp
    HRSoft/Employee.hpp
)

add_executable(hrsoft
    HRSoftMain.cpp
    HRSoft/HRSoftSystem.hpp
    HRSoft/Department.hpp
    HRSoft/Employee.hpp
)

target_compile_options(hrsoft-tests PRIVATE  # <- Ajoute des flags à la compilation
    -Wall  # Ajoute des warnings
    -Wextra  # Ajoute plus de warnings
)

target_compile_options(hrsoft PRIVATE  # <- Ajoute des flags à la compilation
    -Wall  # Ajoute des warnings
    -Wextra  # Ajoute plus de warnings
)


