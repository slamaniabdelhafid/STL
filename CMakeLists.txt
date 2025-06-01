cmake_minimum_required(VERSION 3.10)
project(STL_Container LANGUAGES CXX)

# Set C++ standard and policies
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library target
add_library(circular_list 
    src/circular_list.cpp
)
target_include_directories(circular_list 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Testing configuration
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Download and configure Catch2
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    # Test executable
    add_executable(tests
        tests/test_circular_list.cpp
    )
    target_link_libraries(tests
        PRIVATE
        circular_list
        Catch2::Catch2WithMain
    )

    # Enable testing
    enable_testing()
    add_test(NAME circular_list_tests COMMAND tests)
endif()

# Documentation (optional)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_EXTRACT_ALL YES)
    
    doxygen_add_docs(docs
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        COMMENT "Generating documentation"
    )
endif()
