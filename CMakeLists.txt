cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(glfw_cube LANGUAGES C CXX)

add_subdirectory(pit)
add_subdirectory(dig)
add_subdirectory(launcher)
