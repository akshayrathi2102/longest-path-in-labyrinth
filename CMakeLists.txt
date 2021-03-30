cmake_minimum_required(VERSION 3.10)
project(labyrinth)

set(CMAKE_CXX_STANDARD 11)

add_executable(Labyrinth labyrinth.cpp)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)