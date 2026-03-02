cmake_minimum_required(VERSION 3.16)
project(TP7)

add_executable(ex2
    dungeon/Dungeon.cpp
    dungeon/Entity.hpp
    dungeon/Logger.hpp
    dungeon/Random.cpp
    dungeon/Random.hpp
)

target_compile_features(ex2 PRIVATE cxx_std_17)
target_compile_options(ex2 PRIVATE "-Wfatal-errors")

if(WIN32)
    target_compile_definitions(ex2 PRIVATE "WINDOWS")
endif()