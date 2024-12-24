cmake_minimum_required(VERSION 3.24)
project(lc_easy_cpp CXX)

# cxx standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSTIONS OFF)

# exec
add_executable(${PROJECT_NAME} src/main.cpp)
