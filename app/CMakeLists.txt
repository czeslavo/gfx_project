cmake_minimum_required(VERSION 3.0.0)
project(gfx_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/externals/json
                    ${CMAKE_CURRENT_SOURCE_DIR}/forms)

# app source files
add_subdirectory(source)
include_directories(source)

# gtest/gmock
add_subdirectory(externals/googletest-release-1.8.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include)

# boost libraries
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS
    log log_setup system filesystem date_time thread) 
include_directories(${Boost_INCLUDE_DIRS})

# wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include("${wxWidgets_USE_FILE}")

# tests
enable_testing()
add_subdirectory(tests)
