cmake_minimum_required(VERSION 3.0)
project(PARSER_EXAMPLE)

set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

get_filename_component(PARENT_DIR ${CURRENT_DIR} DIRECTORY)
message(STATUS ${PARENT_DIR})
message(STATUS ${aasdas})

set(SOURCE_DIR ${PARENT_DIR}/src)
set(HEADER_FILES ${SOURCE_DIR}/ArgumentParser.hpp)
include_directories(${SOURCE_DIR})

add_executable(PARSER_EXAMPLE main.cpp ${HEADER_FILES})
