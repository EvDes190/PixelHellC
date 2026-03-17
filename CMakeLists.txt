cmake_minimum_required(VERSION 4.0)
project(PixelHellC C)

set(CMAKE_C_STANDARD 99)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add raylib support
set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    message(STATUS "Getting ${LIB1} from Github")
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local ${LIB1}")
endif()



include_directories("include")
include_directories("include/render")
#include_directories("./raylib/src/include")
#aux_source_directory("raylib/src/lib" RAY)
aux_source_directory("./src" SRC)
aux_source_directory("./src/render" RENDER)


add_executable(PixelHellC main.c
        src/render.c
        src/state.c
        src/pattern.c
#        raylib/src/lib/raylib.dll
#        raylib/src/lib/libraylib.a
#        raylib/src/lib/libraylibdll.a
        include/pattern.h
        include/render.h
        include/state.h
#        raylib/src/include/raymath.h
#        raylib/src/include/raylib.h
#        raylib/src/include/rlgl.h
)

# set the include directory
target_include_directories(PixelHellC PRIVATE ${raylib_INCLUDE_DIRS})

# link all libraries to the project
target_link_libraries(PixelHellC PRIVATE ${LIB1})
target_link_libraries(PixelHellC PRIVATE gdi32 user32)