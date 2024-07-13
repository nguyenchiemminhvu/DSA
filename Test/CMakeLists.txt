cmake_minimum_required(VERSION 3.10)

# Project name
project(DSA_Tests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GoogleTest requires at least C++11
set(gtest_disable_pthreads on)
add_subdirectory(googletest)

# Include directories
include_directories(
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Algorithms/
    ${CMAKE_CURRENT_SOURCE_DIR}/../DataStructures/
)

# Add the header files for Algorithms and DataStructures
include_directories(/usr/local/include/DSA)

# Add compile options
add_compile_options(-std=c++17 -fpermissive)

# List of test files
set(TEST_SOURCES
    main.cpp
    TestArray.cpp
    TestVector.cpp
    TestString.cpp
    TestList.cpp
    TestDeque.cpp
)

# Add the executable for tests
add_executable(DSA_Test ${TEST_SOURCES})

# Link GoogleTest to the test executable
target_link_libraries(DSA_Test gtest gtest_main)

# Enable testing
enable_testing()

# Add test cases
add_test(NAME DSA_Test COMMAND DSA_Test)
