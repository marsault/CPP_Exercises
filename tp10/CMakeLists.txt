cmake_minimum_required(VERSION 3.16)
project(tp10)

add_executable(tp10
    lib/stb_image_write.h
    lib/stb_image.h
    lib/image_lib.hpp
    lib/image_lib.cpp
    src/mandelbrot.cpp
    src/image.hpp
)
target_compile_features(tp10 PRIVATE cxx_std_17)

add_executable(blending
    lib/stb_image_write.h
    lib/stb_image.h
    lib/image_lib.hpp
    lib/image_lib.cpp
    src/blend.cpp
    src/image.hpp
)
target_compile_features(blending PRIVATE cxx_std_17)

add_executable(tranceparence
    lib/stb_image_write.h
    lib/stb_image.h
    lib/image_lib.hpp
    lib/image_lib.cpp
    src/transparency_mask.cpp
    src/image.hpp
)
target_compile_features(tranceparence PRIVATE cxx_std_17)

