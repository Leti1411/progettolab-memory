cmake_minimum_required(VERSION 3.20)
project(PROGETTOLAB)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -U__STRICT_ANSI__")

set(CURSES_INCLUDE_PATH "C:/MinGW/include")
set(CURSES_LIBRARY "C:/MinGW/lib/libpdcurses.a")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.8.1.zip
)

set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
add_subdirectory(test)

add_executable(PROGETTOLAB main.cpp)
target_link_libraries(PROGETTOLAB ${CURSES_LIBRARIES})