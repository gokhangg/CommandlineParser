cmake_minimum_required(VERSION 3.0)
project(parser_example)

add_executable(parser_example main.cpp ${HEADER_FILES})
target_link_libraries(parser_example PUBLIC argument_parser)