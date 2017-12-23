cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 17 ​-Wextra​ ​-Wall​ ​-Wvla​ ​-pthread​)

set(SOURCE_FILES Ex1.cpp Arenstorf.cpp Arenstorf.h ArenstorfPoint.cpp ArenstorfPoint.h)
add_executable(ex1 ${SOURCE_FILES})