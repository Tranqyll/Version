cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

project(Version)
add_executable(${PROJECT_NAME} "main.cpp" "../version.h")
