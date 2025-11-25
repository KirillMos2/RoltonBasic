cmake_minimum_required(VERSION 3.10)
project(roltonbasic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

set(SOURCES
    lexer.cpp
    parser.cpp
    compiler.cpp
    rolton-basic.cpp
)

add_executable(roltonbasic ${SOURCES})
