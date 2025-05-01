cmake_minimum_required(VERSION 3.10)

# Project name
project(DSA_Tests)

# FetchContent to download GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(googletest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GoogleTest requires at least C++11
set(gtest_disable_pthreads on)

# Include directories
include_directories(
    ${googletest_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Algorithms/
    ${CMAKE_CURRENT_SOURCE_DIR}/../DataStructures/
)

# Add compile options
add_compile_options(-std=c++17 -fpermissive -g -fprofile-arcs -ftest-coverage)

# List of test files
set(TEST_SOURCES
    main.cpp
    TestArray.cpp
    TestVector.cpp
    TestString.cpp
    TestList.cpp
    TestDeque.cpp
    TestStack.cpp
    TestQueue.cpp
    TestPriorityQueue.cpp
    TestBinarySearchTree.cpp
    TestAVLTree.cpp
    TestSet.cpp
    TestMap.cpp
    TestHashTable.cpp
    TestUnorderedSet.cpp
    TestUnorderedMap.cpp
    TestBinaryIndexedTree.cpp
    TestTrie.cpp
    TestUnionFind.cpp
    TestGraph.cpp
)

# Add the executable for tests
add_executable(DSA_Test ${TEST_SOURCES})

# Link GoogleTest to the test executable
target_link_libraries(DSA_Test gtest gtest_main gcov gmock)

# Enable testing
enable_testing()

# Add test cases
add_test(NAME DSA_Test COMMAND DSA_Test)

# Custom taret: generate coverage
add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E env TEST_EXECUTABLE=$<TARGET_FILE:DSA_Test> bash ${CMAKE_SOURCE_DIR}/generate_coverage.sh
    DEPENDS DSA_Test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests and generating coverage report"
)
