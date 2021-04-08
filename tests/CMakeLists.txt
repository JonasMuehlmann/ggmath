cmake_minimum_required(VERSION 3.16)
project(ggmath_tests)

set(TEST_FILES
        test.cpp
        test_vec.cpp
        test_util.cpp)

find_package(Threads REQUIRED)
add_executable(ggmath_tests test.cpp ${TEST_FILES})
target_include_directories(ggmath_tests SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries(ggmath_tests PUBLIC Threads::Threads gtest gtest_main ggmath)
