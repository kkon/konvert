cmake_minimum_required(VERSION 3.2)
project(konvert-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3 -g -pedantic")
set(SOURCE_FILES test.cpp)

add_executable(konvert-test ${SOURCE_FILES})
add_test(NAME konvert-15nums-test COMMAND konvert-test)
target_link_libraries(konvert-test konvert)

add_executable(konvert-pf profile.cpp profile_data.h)
add_test(NAME konvert-pf-test COMMAND konvert-pf)
target_link_libraries(konvert-pf konvert)
