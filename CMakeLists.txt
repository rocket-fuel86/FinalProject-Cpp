cmake_minimum_required(VERSION 4.2)
project(final)

set(CMAKE_CXX_STANDARD 26)

add_executable(final main.cpp
        task_data.h
        task_data.cpp
        ui_functions.h
        ui_functions.cpp)
