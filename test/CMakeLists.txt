cmake_minimum_required(VERSION 2.8)
project(konvert-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")
set(SOURCE_FILES test.cpp)

add_executable(konvert-test ${SOURCE_FILES})
add_test(NAME konvert-15nums-test COMMAND konvert-test)
