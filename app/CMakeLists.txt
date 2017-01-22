cmake_minimum_required(VERSION 3.0.0)
project(gfx_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")


# include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/externals/json
                    ${CMAKE_CURRENT_SOURCE_DIR}/forms)

# gtest/gmock
add_subdirectory(externals/googletest-release-1.8.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include)


# app source files
add_subdirectory(source)
include_directories(source)

# tests
enable_testing()
add_subdirectory(tests)
