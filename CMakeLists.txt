cmake_minimum_required(VERSION 3.20)
project(x_tetris C)

set(CMAKE_C_STANDARD 90)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(x_tetris main.c)
target_link_libraries(x_tetris ${CURSES_LIBRARIES})