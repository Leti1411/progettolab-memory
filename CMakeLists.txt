cmake_minimum_required(VERSION 3.30)
project(PROGETTOLAB)

set(CURSES_INCLUDE_PATH "C:/MinGW/include")
set(CURSES_LIBRARY "C:/MinGW/lib/libpdcurses.a")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(PROGETTOLAB main.cpp)
target_link_libraries(PROGETTOLAB ${CURSES_LIBRARIES})




