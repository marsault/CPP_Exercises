cmake_minimum_required(VERSION 3.16)
project(tp02)

add_executable(my_game
    src/Card.cpp
    src/Card.hpp
    src/main.cpp
    src/Value.hpp
    src/Value.cpp
    src/Color.cpp
    src/Color.hpp
    src/Player.cpp
    src/Player.hpp
)

target_compile_features(my_game PRIVATE cxx_std_17)

target_compile_options(my_game PRIVATE 
    -Wall
    -Wextra
    -Werror
)