cmake_minimum_required(VERSION 2.8)
project(konvert)

set(SOURCES include/konvert.h)

add_custom_target(konvert SOURCES ${SOURCES})
set_target_properties(konvert PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(bench)

enable_testing()
add_subdirectory(test)
