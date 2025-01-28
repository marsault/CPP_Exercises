cmake_minimum_required(VERSION 3.16)
project(tp05)

add_executable(ex2
    ex2/main.cpp
    ex2/Card.cpp
    ex2/Player.cpp
    ex2/Tracker.cpp
)


target_compile_features(ex2 PRIVATE cxx_std_17)
