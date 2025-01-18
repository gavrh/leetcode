cmake_minimum_required(VERSION 3.24)
project(lc_medium_cpp CXX)

# cxx standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSTIONS OFF)

# out
add_executable(${PROJECT_NAME} main.cpp)
