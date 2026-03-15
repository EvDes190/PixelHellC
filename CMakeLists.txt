cmake_minimum_required(VERSION 4.0)
project(PixelHellC C)

set(CMAKE_C_STANDARD 99)

include_directories("./include")
include_directories("./include/render")

aux_source_directory("./src" SRC)
aux_source_directory("./src/render" RENDER)


add_executable(PixelHellC main.c
        src/render.c
        src/state.c
        src/pattern.c
        include/pattern.h
        include/render.h
        include/state.h)
