cmake_minimum_required(VERSION 3.16)
project(TP4)

# Add targets for Catch2 dependency
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/Catch2-3.5.2)

# List all exercices
file(GLOB exercice_folders "${CMAKE_CURRENT_SOURCE_DIR}/ex[0-9]*")
foreach(exercice_folder ${exercice_folders})
    get_filename_component(exercice_id ${exercice_folder} NAME_WE)
    
    # Collect the sources for each exercice
    file(GLOB_RECURSE exercice_src CONFIGURE_DEPENDS
        "${exercice_folder}/src/*.cpp"
        "${exercice_folder}/src/*.hpp"
        "${exercice_folder}/src/*.h"
    )

    set(sandbox_file "${exercice_folder}/src/sandbox.cpp")
    MESSAGE("${sandbox_file}")
    MESSAGE("${exercice_src}")
    list(FIND exercice_src "${sandbox_file}" _index)
    if (${_index} GREATER -1)
        MESSAGE("HELLO")
        add_executable("${exercice_id}-sandbox"
            ${exercice_src}
        )
        list(REMOVE_ITEM exercice_src "${exercice_folder}/src/sandbox.cpp")
    endif()
    

    # List all tests
    file(GLOB exercice_tests "${exercice_folder}/tests/*.cpp")
    foreach(exercice_test ${exercice_tests})

        # Generate the name of the executable
        get_filename_component(test_id ${exercice_test} NAME_WE)
        set(target "${exercice_id}-${test_id}")

        # Create an executable from the test file and all the sources
        add_executable(${target}
            ${exercice_src}
            ${exercice_test}
        )

        # Indicate that the executable depends on Catch2
        target_link_libraries(${target} PRIVATE Catch2::Catch2WithMain)

        # Indicate that we use C++17 standard
        target_compile_features(${target} PRIVATE cxx_std_17)

    endforeach()

endforeach()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/configure_targets.cmake)
