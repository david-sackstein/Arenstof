cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 17 ​-Wextra​ ​-Wall​ ​-Wvla​ ​-pthread​)

set(SOURCE_FILES main.cpp Arenstof.cpp Arenstof.h ArenstofPoint.cpp ArenstofPoint.h)
add_executable(ex1 ${SOURCE_FILES})