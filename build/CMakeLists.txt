cmake_minimum_required(VERSION 2.8)
project(Roguelike)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ../src/main.cpp
    ../src/gamemanager.cpp
    ../src/map.cpp
    ../src/units.cpp
    ../src/point.cpp)

add_executable(Roguelike ${SOURCE_FILES})
target_link_libraries( Roguelike ncurses panel )
