# CMake minimum version
cmake_minimum_required(VERSION 2.8)

# Project name
project(quadratic_equation)

# Compil options
add_compile_options(-Wall -Wextra -O2 -std=c99)

# Select build type
set(CMAKE_BUILD_TYPE Debug)

# Adding tests
include(CTest)

# Add command make check
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

# Add path to include 
include_directories(${PROJECT_SOURCE_DIR}/include)

# Adding directories with additional Cmake files
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
