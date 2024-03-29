cmake_minimum_required(VERSION 3.25)
project(C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c)

add_subdirectory(libs)
target_link_libraries(ОП data_structures)
target_link_libraries(ОП algorithms)
