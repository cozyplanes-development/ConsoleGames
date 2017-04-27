cmake_minimum_required(VERSION 3.7)
project(OddEvenGame)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c game.h game.c common.h)
add_executable(OddEvenGame ${SOURCE_FILES})