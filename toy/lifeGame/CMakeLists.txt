cmake_minimum_required(VERSION 3.0)
project(lifeGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(lifeGame main.cpp Game.hpp)
target_link_libraries(lifeGame -lSDL2)