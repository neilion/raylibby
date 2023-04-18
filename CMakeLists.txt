cmake_minimum_required(VERSION 3.25)
project(raylibby)

set(CMAKE_CXX_STANDARD 23)

# ----------------------------------------------------------------------------------------------------------------------
# For dedicated library functions.
# ----------------------------------------------------------------------------------------------------------------------
# Adding this directory will allow for linking to the raylib library.
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/raylib")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/imgui")

# After raylib inclusion, add dependent objects.
file(GLOB SRC_PLOTS
        "src/plotObjects/*.cpp"
        "src/plotObjects/*.h"
        "src/extensions/*.cpp"
        "src/extensions/*.h"
        )

set(PLOTTING_INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/plotObjects/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/extensions/")


# ----------------------------------------------------------------------------------------------------------------------
# raylibby executable
# ----------------------------------------------------------------------------------------------------------------------
## Set up the executable(s) definition(s)
add_executable(raylibby)
target_link_libraries(raylibby PRIVATE raylib)
target_include_directories(raylibby
        PRIVATE
        "${PLOTTING_INCLUDE_DIRS}"
        )
target_sources(raylibby
        PRIVATE
        "main.cpp"
        "${SRC_PLOTS}"
        )
target_compile_definitions(raylibby PRIVATE PLATFORM_DESKTOP)


# ----------------------------------------------------------------------------------------------------------------------
# scatterTest executable
# ----------------------------------------------------------------------------------------------------------------------
add_executable(scatterTest)
target_link_libraries(scatterTest PRIVATE raylib)
target_include_directories(scatterTest
        PRIVATE
        "${PLOTTING_INCLUDE_DIRS}"
        )
target_sources(scatterTest
        PRIVATE
        "src/tests/plotObjects/scatterMain.cpp"
        "${SRC_PLOTS}"
        )

target_compile_definitions(scatterTest PRIVATE PLATFORM_DESKTOP)
target_link_libraries(scatterTest PUBLIC ImGui)


# ----------------------------------------------------------------------------------------------------------------------
# rlImGui
# ----------------------------------------------------------------------------------------------------------------------
## Build rlImGui stuff here, ensures that the the dependencies have already been built
# First, get the rlImGui source files for the static library and the two example executables.
file(GLOB RLIMGUI_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/rlImGui/*.cpp")

file(GLOB RLIMGUI_EXAMPLE_SIMPLE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/rlImGui/examples/simple.cpp")

file(GLOB RLIMGUI_EXAMPLE_EDITOR_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/rlImGui/examples/editor.cpp")

# Include dirs are the same for these three targets.
set(RLIMGUI_INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/rlImGui/")

# TARGET: rlImGui static library
add_library(rlImGui STATIC)
target_sources(rlImGui
        PRIVATE
        "${RLIMGUI_SOURCES}")
target_include_directories(rlImGui
        PRIVATE
        "${RLIMGUI_INCLUDE_DIRS}")
target_link_libraries(rlImGui
        PRIVATE
        raylib
        ImGui)

# TARGET: rlImGui_simple
add_executable(rlImGui_simple)
target_sources(rlImGui_simple
        PRIVATE
        "${RLIMGUI_SOURCES}"
        "${RLIMGUI_EXAMPLE_SIMPLE_SOURCES}"
        )
target_include_directories(rlImGui_simple
        PRIVATE
        "${RLIMGUI_INCLUDE_DIRS}")
target_link_libraries(rlImGui_simple
        PRIVATE
        raylib
        ImGui)

# TARGET: rlImGui_editor
add_executable(rlImGui_editor)
target_sources(rlImGui_editor
        PRIVATE
        "${RLIMGUI_SOURCES}"
        "${RLIMGUI_EXAMPLE_EDITOR_SOURCES}"
        )
target_include_directories(rlImGui_editor
        PRIVATE
        "${RLIMGUI_INCLUDE_DIRS}")
target_link_libraries(rlImGui_editor
        PRIVATE
        raylib
        ImGui)