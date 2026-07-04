cmake_minimum_required(VERSION 4.2)
project(Personal_Dashboard)

set(CMAKE_CXX_STANDARD 20)

add_executable(Personal_Dashboard main.cpp
        tasks.h
        tasks.cpp)
target_include_directories(Personal_Dashboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})