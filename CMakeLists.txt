cmake_minimum_required(VERSION 3.2)
project(konvert)


add_library(konvert INTERFACE)

target_include_directories(konvert INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/konvert>
)

install(FILES include/konvert.h DESTINATION include)

add_custom_target(konvert_headers SOURCES include/konvert.h)
set_target_properties(konvert_headers PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(bench)

enable_testing()
add_subdirectory(test)
