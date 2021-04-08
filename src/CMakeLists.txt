cmake_minimum_required(VERSION 3.16)
project(ggmath)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src)

set(HEADER_FILES
        vec.hpp
        mat.hpp
        graphics.hpp
        intersection.hpp
        physics.hpp
        ray.hpp
        types.hpp
        util.hpp)

add_library(ggmath STATIC ${HEADER_FILES})

# target_compile_definitions(ggmath PUBLIC GGMATH_DEBUG)
set_target_properties(ggmath PROPERTIES LINKER_LANGUAGE CXX)
