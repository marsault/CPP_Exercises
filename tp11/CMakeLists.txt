cmake_minimum_required(VERSION 3.16)
project(tp11)

add_executable(factory
    src/factory.cpp
)
target_compile_features(factory PRIVATE cxx_std_17)

add_executable(print
    src/tostring.cpp
)
target_compile_features(factory PRIVATE cxx_std_17)
