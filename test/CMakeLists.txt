cmake_minimum_required(VERSION 2.8)
project(konvert-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3 -g -pedantic")
set(SOURCE_FILES test.cpp)

add_executable(konvert-test ${SOURCE_FILES})
add_test(NAME konvert-15nums-test COMMAND konvert-test)

add_executable(konvert-pf profile.cpp)
add_test(NAME konvert-pf-test COMMAND konvert-pf)
