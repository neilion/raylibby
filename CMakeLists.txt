cmake_minimum_required(VERSION 3.25)
project(raylibby)

set(CMAKE_CXX_STANDARD 23)


# Adding this directory will allow for linking to the raylib library.
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/raylib")

# After raylib inclusion, add dependent objects.
file(GLOB SRC_PLOTS
        "src/plotObjects/*.cpp"
        "src/plotObjects/*.h"
        "src/extensions/*.cpp"
        "src/extensions/*.h"
        )

set(INCS_PLOT
        "${CMAKE_CURRENT_SOURCE_DIR}/src/plotObjects/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/extensions/")


function (newlines numLines)
    foreach ( index RANGE ${numLines} )
        message("\n")
    endforeach ()
endfunction()



newlines("2")
foreach (STR IN LISTS SRC_PLOTS)
    message(STATUS "${STR}")
endforeach ()
newlines("2")

newlines("2")
foreach (STR IN LISTS INCS_PLOT)
    message(STATUS "${STR}")
endforeach ()
newlines("2")

## Set up the executable(s) definition(s)
add_executable(raylibby)
target_link_libraries(raylibby PRIVATE raylib)
target_include_directories(raylibby
        PRIVATE
        "${INC_PLOTS}"
        )
target_sources(raylibby
        PRIVATE
        "main.cpp"
        "${SRC_PLOTS}"
        )
target_compile_definitions(raylibby PRIVATE PLATFORM_DESKTOP)

add_executable(scatterTest)
target_link_libraries(scatterTest PRIVATE raylib)
target_include_directories(scatterTest
        PRIVATE
        "${INCS_PLOT}"
        )
target_sources(scatterTest
        PRIVATE
        "src/tests/plotObjects/scatterMain.cpp"
        "${SRC_PLOTS}"
        )

target_compile_definitions(scatterTest PRIVATE PLATFORM_DESKTOP)