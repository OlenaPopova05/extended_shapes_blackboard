cmake_minimum_required(VERSION 3.28)
project(extended_shapes_blackboard)

set(CMAKE_CXX_STANDARD 17)

add_executable(extended_shapes_blackboard main.cpp
        Board.h
        Board.cpp
        Figure.h
        Figure.cpp
        FileHandler.h
        FileHandler.cpp)
