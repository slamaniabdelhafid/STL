cmake_minimum_required(VERSION 3.14)
project(STL_Container LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library target
add_library(circular_list
    src/circular_list.cpp
)
target_include_directories(circular_list
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Testing
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG devel
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(tests tests/test_circular_list.cpp)
    target_link_libraries(tests PRIVATE circular_list Catch2::Catch2WithMain)
    
    enable_testing()
    add_test(NAME circular_list_tests COMMAND tests)
endif()

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    
    doxygen_add_docs(docs
        ${CMAKE_CURRENT_SOURCE_DIR}/include/circular_list.hpp
        COMMENT "Generating documentation"
    )
endif()
