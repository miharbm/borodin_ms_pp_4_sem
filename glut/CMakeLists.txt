cmake_minimum_required(VERSION 3.21)
project(glut)

set(CMAKE_CXX_STANDARD 17 -framework GLUT -framework OpenGL)

add_executable(glut main.cpp)
