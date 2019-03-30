cmake_minimum_required(VERSION 3.13)
project(task3_ls C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

add_executable(task3_ls main.c)