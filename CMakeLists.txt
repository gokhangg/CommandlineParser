cmake_minimum_required(VERSION 3.0)
project(COMMANDLINE_PARSER)

set(TEST_DIR ${CMAKE_SOURCE_DIR}/Test)
set(EXAMPLE_DIR ${CMAKE_SOURCE_DIR}/Example)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

option(BUILD_TEST "If test is wanted.")


if (BUILD_TEST)
	add_subdirectory(${TEST_DIR})
endif()

add_subdirectory(${EXAMPLE_DIR})
