cmake_minimum_required(VERSION 3.25)
project(ОП)

set(CMAKE_C_STANDARD 11)

add_executable(ОП main.c)

add_subdirectory(libs)
target_link_libraries(ОП data_structures)
target_link_libraries(ОП algorithms)
target_link_libraries(ОП str)