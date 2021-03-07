cmake_minimum_required(VERSION 3.0.0)
project(Tetris VERSION 0.1.0)

add_executable(Tetris src/main.cpp src/Block.cpp src/Grid.cpp)
set_property(TARGET Tetris PROPERTY CXX_STANDARD 17)

target_link_libraries(Tetris sfml-graphics sfml-window sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
