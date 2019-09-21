cmake_minimum_required(VERSION 3.10)
project(table_tannis_champ_simulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(table_tannis_champ_simulation main.cpp Table.hpp Table.cpp Player.hpp Player.cpp Ball.hpp Ball.cpp Judge.hpp Judge.cpp App.hpp App.cpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(table_tannis_champ_simulation ${CURSES_LIBRARIES} -pthread)