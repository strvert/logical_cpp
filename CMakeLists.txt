cmake_minimum_required(VERSION 3.12)

project(logical_cpp)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ./inc)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Ofast -Wall)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -lfmt)

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
