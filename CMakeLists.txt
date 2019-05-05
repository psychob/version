cmake_minimum_required(VERSION 3.14)
project(version)

set(CMAKE_CXX_STANDARD 11)

add_executable(version main.cpp version.hpp version.cpp)