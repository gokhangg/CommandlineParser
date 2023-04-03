cmake_minimum_required(VERSION 3.0)
project(COMMANDLINE_PARSER)

set (CMAKE_CXX_STANDARD 17)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/example)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/arg_parser)


option(BUILD_TEST "If test is wanted.")
option(BUILD_EXAMPLE "If the example is wanted.")

add_library(argument_parser STATIC)
target_include_directories(argument_parser PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_sources(argument_parser PRIVATE ${PROJECT_SOURCE_DIR}/src/argument_parser.cpp)

if (BUILD_TEST)
	add_subdirectory(${TEST_DIR})
endif()
if (BUILD_EXAMPLE)
    add_subdirectory(${EXAMPLE_DIR})
endif()