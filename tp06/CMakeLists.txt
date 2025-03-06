cmake_minimum_required(VERSION 3.16)
project(TP6)

add_executable(ex1
    1-recipes/main.cpp
    1-recipes/Material.hpp
    1-recipes/ProgramData.cpp
    1-recipes/ProgramData.hpp
    1-recipes/Recipe.hpp
    1-recipes/lib/ActionManager.hpp
)
target_compile_features(ex1 PRIVATE cxx_std_17)

add_executable(ex2
    2-ptr/main.cpp
    2-ptr/Object.hpp
    2-ptr/CopyablePtr.hpp
)

file(GLOB SAVES
  "${CMAKE_SOURCE_DIR}/1-recipes/cmake/*.txt"
)
file(COPY ${SAVES} DESTINATION "${CMAKE_BINARY_DIR}")

target_compile_features(ex2 PRIVATE cxx_std_17)
