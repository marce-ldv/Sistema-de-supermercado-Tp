cmake_minimum_required(VERSION 3.8)
project(tp_2do)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c TDA_general.c TDA_general.h matriz.c matriz.h)
add_executable(tp_2do ${SOURCE_FILES} TDA_general.c TDA_general.h)