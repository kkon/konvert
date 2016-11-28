cmake_minimum_required(VERSION 2.8)
project(bench)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3 -pedantic")
set(SOURCE_FILES main.cpp lbench.h)

add_executable(konvert-bench ${SOURCE_FILES})
set_property(TARGET konvert-bench PROPERTY CXX_STANDARD 14)