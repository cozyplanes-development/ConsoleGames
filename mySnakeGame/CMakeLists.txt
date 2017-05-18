cmake_minimum_required(VERSION 3.7)
project(mySnakeGame)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c snake.c snake.h)
add_executable(mySnakeGame ${SOURCE_FILES})