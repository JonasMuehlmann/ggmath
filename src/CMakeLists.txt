cmake_minimum_required(VERSION 3.17)
project(ggmath)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src)

set(SOURCE_FILES
        vec.cpp
        mat.cpp
        )

set(HEADER_FILES
        vec.hpp
        mat.hpp
        )
add_library(ggmath STATIC ${SOURCE_FILES} ${HEADER_FILES})