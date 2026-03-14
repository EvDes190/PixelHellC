cmake_minimum_required(VERSION 4.0)
project(PixelHellC C)

set(CMAKE_C_STANDARD 99)

# Our Project
add_executable(PixelHellC main.c
        render/window.c
        src/state.c
        src/pattern.c
        src/patterns.c)
