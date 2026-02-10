cmake_minimum_required(VERSION 3.10)
project(PROGETTOLAB)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Attivita.cpp Registro.cpp Attivita.h Registro.h)
add_library(core ${SOURCE_FILES})

set(CURSES_INCLUDE_PATH "C:/MinGW/include")
set(CURSES_LIBRARY "C:/MinGW/lib/libpdcurses.a")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(PROGETTOLAB main.cpp)
target_link_libraries(PROGETTOLAB core ${CURSES_LIBRARIES})

add_subdirectory(test)