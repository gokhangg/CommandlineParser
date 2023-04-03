cmake_minimum_required(VERSION 3.0)
project(parser_test)

include(GoogleTest)
set(gtest_force_shared_crt TRUE CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest EXCLUDE_FROM_ALL)

add_executable(parser_test tests.cpp)
target_link_libraries(parser_test PUBLIC gtest_main argument_parser)