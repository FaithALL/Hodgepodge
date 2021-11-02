cmake_minimum_required(VERSION 3.0)
project(lifeGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(lifeGame main.cpp Game.hpp)
target_link_libraries(lifeGame ${SDL2_LIBRARIES})
