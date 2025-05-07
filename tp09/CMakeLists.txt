cmake_minimum_required(VERSION 3.16)
project(tp09)

add_executable(ex3
    Point2d.cpp
)

add_executable(ex4
    Point3d.cpp
)

target_compile_features(ex3 PRIVATE cxx_std_17)
target_compile_features(ex4 PRIVATE cxx_std_17)

# add_executable(ex3
#     ex3/main.cpp
#     ex3/LinkedList.cpp
#     ex3/Link.cpp
#     ex3/Tracker.cpp
#     ex3/Person.cpp
# )

# target_compile_features(ex3 PRIVATE cxx_std_17)
# target_compile_features(ex3 PRIVATE )
