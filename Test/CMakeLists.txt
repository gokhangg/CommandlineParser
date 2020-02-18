cmake_minimum_required(VERSION 3.0)
project(PARSER_TEST)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/gtestExternal)

include(ExternalProject)
ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include ${CMAKE_SOURCE_DIR}/src)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

if (MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_executable(PARSER_TEST main.cpp)

add_dependencies(PARSER_TEST googletest)
target_link_libraries(PARSER_TEST debug gtestd)
target_link_libraries(PARSER_TEST optimized gtest)